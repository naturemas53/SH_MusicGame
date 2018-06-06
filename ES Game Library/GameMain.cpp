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
	RawInputReceiver& receiver = GameApp().GetReceiver();
	receiver.InitDeviceStatus();
	HANDLE RIDEV = SceneShared().GetDataForKey("Player1");
	SceneShared().RemoveDataForKey("Player1");

	receiver.AddMouseListener(RIDEV, &mouse_state[0]);

	RIDEV = SceneShared().GetDataForKey("Player2");
	SceneShared().RemoveDataForKey("Player2");
	receiver.AddMouseListener(RIDEV, &mouse_state[1]);


	
	chara1 = GraphicsDevice.CreateSpriteFromFile(_T("p1.png"));
	chara2 = GraphicsDevice.CreateSpriteFromFile(_T("1.png"));

	chara1_x = 0.0f;
	chara1_y = 0.0f;

	chara2_x = 0.0f;
	chara2_y = 0.0f;

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


	chara1_x += mouse_state[0].diff_x();
	chara1_y += mouse_state[0].diff_y();

	mouse_state[0].reset();

	chara2_x += mouse_state[1].diff_x();
	chara2_y += mouse_state[1].diff_y();

	mouse_state[1].reset();

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
	SpriteBatch.Draw(*chara1, Vector3(chara1_x, chara1_y, 0.0f));
	SpriteBatch.Draw(*chara2, Vector3(chara2_x, chara2_y, 0.0f));

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
