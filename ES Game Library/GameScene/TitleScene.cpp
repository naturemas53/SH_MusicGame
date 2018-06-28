#include "../StdAfx.h"
#include "TitleScene.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool TitleScene::Initialize()
{
	// TODO: Add your initialization logic here
	this->font_ = GraphicsDevice.CreateDefaultFont();

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void TitleScene::Finalize()
{
	// TODO: Add your finalization logic here

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
	RawInputMouse leftMouse = MultiMouse.GetInputData(0);
	RawInputMouse righttMouse = MultiMouse.GetInputData(1);

	if (leftMouse.IsPushed(LEFTBUTTON) || righttMouse.IsPushed(LEFTBUTTON)){
		return GAME_SCENE(new LoadingScene());
	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void TitleScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	SpriteBatch.DrawString(this->font_,Vector2_Zero,Color(0,0,0),_T("TITLE SCENE"));
	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
