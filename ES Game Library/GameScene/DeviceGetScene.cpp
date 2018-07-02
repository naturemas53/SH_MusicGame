#include "../StdAfx.h"
#include "DeviceGetScene.hpp"
#include <typeinfo>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool DeviceGetScene::Initialize()
{
	// TODO: Add your initialization logic here
	this->font_ = GraphicsDevice.CreateDefaultFont();
	this->fade_.ChangeFade(FadeInOut::FADE_IN,1);
	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void DeviceGetScene::Finalize()
{
	// TODO: Add your finalization logic here
	this->fade_.ReleaseRenderTarget();
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int DeviceGetScene::Update()
{
    // TODO: Add your update logic here
	if (MultiMouse.GetDeviceCount() >= 2){

		MultiMouse.StartListening();
		if (this->fade_.GetType() == FadeInOut::FADE_IN)
			this->fade_.ChangeFade(FadeInOut::FADE_OUT,1000);

	}

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT)
		return GAME_SCENE(new TitleScene);

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void DeviceGetScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();

	SpriteBatch.DrawString(this->font_, Vector2_Zero, Color(255, 255, 255), _T("PLEASE MOUSE CLICK REMAIN %d"), 2 - MultiMouse.GetDeviceCount());
	GraphicsDevice.ClearZBuffer();
	this->fade_.Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
