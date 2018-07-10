#include "../StdAfx.h"
#include "LoadingScene.hpp"
#include "../MakeClasses/yoshi/SceneLoadSingleton.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool LoadingScene::Initialize()
{
	// TODO: Add your initialization logic here

	this->load_image = GraphicsDevice.CreateSpriteFromFile(_T("LoadingScene/manyuaru_game.png"));
	this->fade_.ChangeFade(FadeInOut::FADE_IN,200);

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void LoadingScene::Finalize()
{
	// TODO: Add your finalization logic here
	GraphicsDevice.ReleaseSprite(this->load_image);
	this->fade_.ReleaseRenderTarget();
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int LoadingScene::Update()
{
    // TODO: Add your update logic heres

	if (AsyncLoadScene.IsComplete(&this->nextScene_) && this->fade_.GetType() == FadeInOut::FADE_IN)
	{
		this->fade_.ChangeFade(FadeInOut::FADE_OUT,500);
	}
	
	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT){
		return this->nextScene_;
	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void LoadingScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	SpriteBatch.Draw(*load_image, Vector3_Zero, 1.0f);
	this->fade_.Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}