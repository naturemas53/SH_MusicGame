#include "../StdAfx.h"
#include "ResultScene.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool ResultScene::Initialize()
{
	// TODO: Add your initialization logic here
	this->result_image = GraphicsDevice.CreateSpriteFromFile(_T("stage1_bg.png"));
	this->score_font = GraphicsDevice.CreateDefaultFont();
	this->combo_font = GraphicsDevice.CreateDefaultFont();
	this->perfect_font = GraphicsDevice.CreateDefaultFont();
	this->great_font = GraphicsDevice.CreateDefaultFont();
	this->miss_font = GraphicsDevice.CreateDefaultFont();

	//透明
	load_alpa = 1.0f;
	load_state = 0;
	font_delete = false;

	//でばばば
	this->counter_.perfect = 100;
	this->counter_.great = 10;
	this->counter_.miss = 893;
	
	this->score_ = 37564;
	this->perfect = 500000;
	this->great = 40000;
	this->miss = 444444;//yoshi


	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void ResultScene::Finalize()
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
int ResultScene::Update()
{
    // TODO: Add your update logic here

	RawInputMouse leftMouse = MultiMouse.GetInputData(0);
	RawInputMouse rightMouse = MultiMouse.GetInputData(1);
//タイトル戻るフェード
	if (leftMouse.IsPushed(LEFTBUTTON) || rightMouse.IsPushed(LEFTBUTTON))
	{
		font_delete = true;
		load_state = 1;
		
	}
	if (load_state == 1)
	{
		load_alpa -= 0.01f;
		if (load_alpa <= 0)
		{
			return GAME_SCENE(new TitleScene());

		}

	}



	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void ResultScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();
	// 文字列の描画
	SpriteBatch.Begin();
	SpriteBatch.Draw(*result_image, Vector3(0.0f, 0.0f, 0.0f),load_alpa);
	/*this->counter_.perfect = 100;
	this->counter_.great = 10;
	this->counter_.miss = 893;
*/
	if (!font_delete)
	{
		
		SpriteBatch.DrawString(score_font, Vector2(260.0f, 100.0f), Color(0.0f, 200.0f, 0.0f), _T("%d "), score_);
		//SpriteBatch.DrawString(combo_font, Vector2(260.0f, 200.0f), Color(0.0f, 200.0f, 0.0f), _T("%d "), combo);
		SpriteBatch.DrawString(perfect_font, Vector2(260.0f, 300.0f), Color(0.0f, 200.0f, 0.0f), _T("%d "), perfect);
		SpriteBatch.DrawString(great_font, Vector2(260.0f, 400.0f), Color(0.0f, 200.0f, 0.0f), _T("%d "), great);
		SpriteBatch.DrawString(miss_font, Vector2(260.0f, 500.0f), Color(0.0f, 200.0f, 0.0f), _T("%d "), miss);


	}


	




	SpriteBatch.End();
	GraphicsDevice.EndScene();




}
