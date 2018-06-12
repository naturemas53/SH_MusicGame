// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include "Framework\GameApp.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	mousepos[0] = Vector2_Zero;
	mousepos[1] = Vector2_Zero;

	GameApp().StartLisening();
	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
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
int GameMain::Update()
{
	// TODO: Add your update logic here

	for (int i = 0; i < 2;i++){

		mousepos[i].x += GameApp().GetMouseValue(i, GameApp().X) ;
		mousepos[i].y += GameApp().GetMouseValue(i, GameApp().Y) ;

	}

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

	for (int i = 0; i < 2; i++){

		SpriteBatch.DrawString(DefaultFont,mousepos[i],Color(255,255,255),_T("%dP"),i);

		if (GameApp().GetMouseValue(i, GameApp().BUTTON0)){
			SpriteBatch.DrawString(DefaultFont, Vector2(0.0f,100.0f * i), Color(0, 0, 0), _T("%dP LEFT PUSH"), i);
		}
		if (GameApp().GetMouseValue(i, GameApp().BUTTON1)){
			SpriteBatch.DrawString(DefaultFont, Vector2(100.0f, 100.0f * i), Color(0, 0, 0), _T("%dP RIGHT PUSH"), i);
		}

	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
