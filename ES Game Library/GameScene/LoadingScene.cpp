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

	this->load_image = GraphicsDevice.CreateSpriteFromFile(_T("nowloading.png"));
	this->load_alpha_ = 0.0f;
	this->alpha_state_ = UP;
	this->fade_.ChangeFade(FadeInOut::FADE_IN,500);

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
    // TODO: Add your update logic here

	switch (this->alpha_state_){
	case ALPHA_STATE::UP:
		this->load_alpha_ += 0.03f;
		if (this->load_alpha_ >= 1.0f){
			this->load_alpha_ = 1.0f;
			this->alpha_state_ = DOWN;
		}

		break;
	case ALPHA_STATE::DOWN:
		this->load_alpha_ -= 0.03f;
		if (this->load_alpha_ <= 0.0f){
			this->load_alpha_ = 0.0f;
			this->alpha_state_ = UP;
		}

		break;
	}

	if (AsyncLoadScene.IsComplete(&this->nextScene_) && this->fade_.GetType() == FadeInOut::FADE_IN)
	{
		this->fade_.ChangeFade(FadeInOut::FADE_OUT,800);
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

	SpriteBatch.Draw(*load_image, Vector3(350, 400, 0.0f), this->load_alpha_);
	this->fade_.Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}