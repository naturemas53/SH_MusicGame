#include "../StdAfx.h"
#include "LoadingScene.hpp"
#include <thread>
#include <chrono>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool LoadingScene::Initialize()
{
	// TODO: Add your initialization logic here
	auto scene = [](){
		return GAME_SCENE(new GameMain());
	};

	this->gameScene_ = std::async(std::launch::async,scene);
	this->font_ = GraphicsDevice.CreateDefaultFont();

	this->value_ = 0;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void LoadingScene::Finalize()
{
	// TODO: Add your finalization logic here
	GraphicsDevice.ReleaseFont(this->font_);
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

	if (this->gameScene_.wait_for(std::chrono::seconds(0)) == std::future_status::ready){

		return this->gameScene_.get();

	}

	this->value_++;

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void LoadingScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	SpriteBatch.DrawString(this->font_,Vector2_Zero,Color(0,0,0),_T("LOADING NOW... %d"),this->value_);

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
