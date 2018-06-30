#include "../StdAfx.h"
#include "TitleScene.hpp"
#include "../MakeClasses/yoshi/SceneLoadSingleton.h"
#include <thread>

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
	this->title_image = GraphicsDevice.CreateSpriteFromFile(_T("title.png"));
	this->click_image = GraphicsDevice.CreateSpriteFromFile(_T("game_start_ward.png"));
	this->now_load_image = GraphicsDevice.CreateSpriteFromFile(_T("nowloading.png"));

	//ナウロード関連
	now_load_alpa = 1.0f;
	now_load_state = 0;
	nou_load_flag = false;


	//クリック関連
	click_alpa = 1.0f;
	click_state = 0;
	click_delete = false;

	//タイトルの関連
	title_state = 0;
	title_alpa = 1.0f;

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
	RawInputMouse rightMouse = MultiMouse.GetInputData(1);
	
		

	//タイトルアルファ減らす　０なったら非同期へ
		if (leftMouse.IsPushed(LEFTBUTTON) || rightMouse.IsPushed(LEFTBUTTON))
		{
			click_delete = true;
			title_state = 1;
			nou_load_flag = true;
			AsyncLoadScene.SetAsyncLoad(std::async(std::launch::async, [](){ return GAME_SCENE(new GameMain()); }));


		}
		if (nou_load_flag == true)
		{
			Transparent();
		}

			if (title_state == 1)
			{
				title_alpa -= 0.01f;
			}

			if (title_state == 1 && title_alpa <= 0)
				{
					return GAME_SCENE(new LoadingScene());
					title_state = 0;
				}

			//クリックしてね透明不透明
			if (click_state == 0)
			{
				click_alpa -= 0.01f;

				if (click_alpa <= 0)
				{
					click_state = 1;
				}
				
			}
			if (click_state == 1)
			{
				click_alpa += 0.01f;
				if (click_alpa >= 1)
				{
					click_state = 0;
				}
			}
		

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void TitleScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	SpriteBatch.DrawString(this->font_, Vector2_Zero, Color(0, 200, 0), _T("TITLE SCENE"));
	SpriteBatch.Draw(*title_image, Vector3(0,0,0), title_alpa);
	if (nou_load_flag == true)
	{
		SpriteBatch.Draw(*now_load_image, Vector3(350, 400, -100.0f), now_load_alpa);

	}


	//
	////クリックしたら描画しない
	if (!click_delete)
	{
		SpriteBatch.Draw(*click_image, Vector3(480.0f, 360.0f, 0), click_alpa);

	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}

void TitleScene::Transparent()
{
	if (now_load_state == 0)
	{
		now_load_alpa -= 0.01f;
		if (now_load_alpa <= 0.0f)
		{
			now_load_state = 1;
		}
	}

	if (now_load_state == 1)
	{
		now_load_alpa += 0.01f;
		if (click_alpa >= 1)
		{
			click_state = 0;
		}
	}
}
