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

	this->font_ = GraphicsDevice.CreateDefaultFont();
	this->load_image = GraphicsDevice.CreateSpriteFromFile(_T("nowloading.png"));
	this->asynchronous_image = GraphicsDevice.CreateSpriteFromFile(_T("stage_select_haikei.png"));


	load_alpa = 1.0f;
	load_state = 1.0f;
	


	this->value_ = 0;
	load_derite_flag = false;

	nextload_alpa = 1.0f;
	nextload_state = 0;
	this->nextScene_ = 0;
	this->load_state = 0;

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

		if (load_state == 0)
		{
			load_alpa -= 0.01f;
			if (load_alpa <= 0.0f)
			{
				if (AsyncLoadScene.IsComplete(&this->nextScene_))
				{
					load_state = 1;

				}
			}
		}

		if (load_state == 1)
		{
			Next_Load_Fade();
			load_derite_flag = true;
			if (nextload_flag == true)
			{
				return this->nextScene_;
			}
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
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	if (!load_derite_flag)
	{
		SpriteBatch.Draw(*load_image, Vector3(350, 400, -100.0f), load_alpa);

	}



	SpriteBatch.Draw(*asynchronous_image, Vector3(0.0f, 0.0f, 0.0f), nextload_alpa,
		Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.7f);


	/*SpriteBatch.Draw(*this->numberSp_, Vector3(450.0f, 600.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f), 0.5f);

*/
	
	SpriteBatch.DrawString(this->font_,Vector2_Zero,Color(50,250,50),_T("LOADING NOW... %d"),this->value_);


	SpriteBatch.End();

	GraphicsDevice.EndScene();
}

//フェード関数
void LoadingScene::Next_Load_Fade()
{
	if (nextload_state == 0)
	{
		nextload_alpa -= 0.01f;
		if (nextload_alpa <= 0)
		{
			nextload_state = 1;
			nextload_flag = true;
		}
	}

	/*if (nextload_state == 1)
	{
		nextload_alpa += 0.01f;
		if (nextload_alpa >= 1.0f)
		{
			nextload_state = 0;
		}

	}*/
}
