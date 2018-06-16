// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include "MakeClasses\Fujimura\DataSingleton.h"
#include "MakeClasses\Fujimura\Judgement\JudgeContext.h"
#include "MakeClasses\Fujimura\Lane\Lane.h"
#include "MakeClasses\Fujimura\Note\Note\Note.h"
#include "MakeClasses\Fujimura\MusicScoreIO.h"
#include <functional>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));
	Data.LoadSprite(_T("kari_atlas.png"));

	this->judgeContext_ = new JudgeContext();
	Lane* lane = new Lane(Vector3(0.0f, 620.0f, 0.0f), this->judgeContext_, 0);
	this->lanes_.push_back(lane);

	lane = new Lane(Vector3(1280.0f - 512.0f, 620.0f, 0.0f), this->judgeContext_, 1);
	this->lanes_.push_back(lane);

	MusicScoreIO scoreIo("musicscore.txt");
	scoreIo.ImportScore(this->lanes_);

	this->bgm_ = SoundDevice.CreateSoundFromFile(_T("music.wav"));
	this->bgm_->Play();


	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here

	for (auto lane : this->lanes_){ delete lane; }

	delete this->judgeContext_;
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here
	for (auto lane : this->lanes_) lane->Update(this->bgm_->GetCurrentMilliSec());

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	for (auto lane : this->lanes_) lane->Draw(this->bgm_->GetCurrentMilliSec());

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
