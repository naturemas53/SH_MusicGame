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
	this->clickStrSp_ = GraphicsDevice.CreateSpriteFromFile(_T("TitleScene/cleck_to_start.png"));
	this->fade_.ChangeFade(FadeInOut::FADE_IN,200);
	this->strAlpha_ = 0.0f;
	this->alpha_state_ = ALPHA_STATE::UP;

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
	GraphicsDevice.ReleaseSprite(this->clickStrSp_);
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

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT){
		return this->nextScene_;
	}

	if(this->fade_.GetType() == FadeInOut::FADE_OUT){
	
		return 0;
	
	}

	RawInputMouse leftMouse = MultiMouse.GetInputData(0);
	RawInputMouse rightMouse = MultiMouse.GetInputData(1);

	if(AsyncLoadScene.IsComplete(&this->nextScene_)){
	
		this->AlphaUpdate();

	}

	if ( (leftMouse.IsPushed(LEFTBUTTON) || leftMouse.IsPushed(RIGHTBUTTON) ||
		rightMouse.IsPushed(LEFTBUTTON) || rightMouse.IsPushed(RIGHTBUTTON))&&
		AsyncLoadScene.IsComplete(&this->nextScene_) && 
		this->fade_.GetType() == FadeInOut::FADE_IN)
	{
		this->fade_.ChangeFade(FadeInOut::FADE_OUT,500);
		this->strAlpha_ = 0.0f;
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

	float clickStrWidth = 369.0f;
	float posX = (1280.0f - clickStrWidth) / 2.0f;
	SpriteBatch.Draw(*this->clickStrSp_, Vector3(posX,140.0f,0.0f), this->strAlpha_);

	this->fade_.Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}

void LoadingScene::AlphaUpdate(){

		float movement = 0.02f;

	switch (this->alpha_state_){
	case ALPHA_STATE::UP:

		this->strAlpha_ += movement;
		if (this->strAlpha_ >= 1.0f){
			this->strAlpha_ = 1.0f;
			this->alpha_state_ = DOWN;
		}

		break;
	case ALPHA_STATE::DOWN:
		this->strAlpha_ -= movement;
		if (this->strAlpha_ <= 0.0f){
			this->strAlpha_ = 0.0f;
			this->alpha_state_ = UP;
		}

		break;
	}

}