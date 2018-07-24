#include "../StdAfx.h"
#include "TitleScene.hpp"
#include "../MakeClasses/yoshi/SceneLoadSingleton.h"
#include <thread>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool TitleScene::Initialize()
{
	// TODO: Add your initialization logic here
	this->context_.Initialize();
	this->fade_.ChangeFade(FadeInOut::FADE_IN,500);

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void TitleScene::Finalize()
{
	// TODO: Add your finalization logic here
	this->context_.Finalize();
	this->fade_.ReleaseRenderTarget();

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int TitleScene::Update()
{
    // TODO: Add your update logic here

	this->context_.Update();

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT){

		return GAME_SCENE(new LoadingScene());

	}

	if (this->fade_.GetType() == FadeInOut::FADE_OUT){
		return 0;
	}
		
	RawInputMouse leftMouse = MultiMouse.GetInputData(0);
	RawInputMouse rightMouse = MultiMouse.GetInputData(1);

	if (leftMouse.IsPushed(LEFTBUTTON) || rightMouse.IsPushed(LEFTBUTTON)){

		this->fade_.ChangeFade(FadeInOut::FADE_OUT,700);

		AsyncLoadScene.SetAsyncLoad(std::async(std::launch::async, [](){ 
			int scene = GAME_SCENE(new GameMain); 
			reinterpret_cast<GameMain*>(scene)->ObjectInitialize();
			return scene;
		}));

	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void TitleScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	this->context_.Draw();

	this->fade_.Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}