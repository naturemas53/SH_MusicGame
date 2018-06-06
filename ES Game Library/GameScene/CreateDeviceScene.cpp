#include "../StdAfx.h"
#include "CreateDeviceScene.hpp"
#include "../Framework/GameApp.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool CreateDeviceScene::Initialize()
{
	// TODO: Add your initialization logic here
	RawInputReceiver& receiver = GameApp().GetReceiver();

	receiver.AddMouseListener(RIDEV_DEFAULT, &mouse_detector);


	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void CreateDeviceScene::Finalize()
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
int CreateDeviceScene::Update()
{
    // TODO: Add your update logic here

	if (mouse_detector.getDeviceCount() >= 2)
	{

		SceneShared().SetDataForKey("Player1",mouse_detector.getDeviceID(0));
		SceneShared().SetDataForKey("Player2", mouse_detector.getDeviceID(1));

		return GAME_SCENE(new GameMain());
	}
	

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void CreateDeviceScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	GraphicsDevice.EndScene();
}
