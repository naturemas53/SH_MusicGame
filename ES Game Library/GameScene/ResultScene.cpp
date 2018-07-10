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

	this->judgeSp_ = GraphicsDevice.CreateSpriteFromFile(_T("judges.png"));
	this->numberSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_01.png"));
	this->growSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_02.png"));
	this->scoreSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/score_text.png"));
	this->thankStrSp_ = GraphicsDevice.CreateSpriteFromFile(_T("ResultScene/result_text.png"));
	this->thankGrowSp_ = GraphicsDevice.CreateSpriteFromFile(_T("ResultScene/result_text_grow.png"));

	this->score_ = SceneShared().GetIntegerForKey("SCORE");
	JudgeCounter* counter = (JudgeCounter*)SceneShared().GetDataForKey("JUDGECOUNTER");
	this->counter_ = *counter;

	delete counter;

	SceneShared().RemoveIntegerForKey("SCORE");
	SceneShared().RemoveDataForKey("JUDGECOUNTER");

	this->fade_.ChangeFade(FadeInOut::FADE_IN,500);

	this->elapsedTime_ = 0;

	this->alpha_state_ = DOWN;

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void ResultScene::Finalize()
{
	// TODO: Add your finalization logic here
	GraphicsDevice.ReleaseSprite(this->result_image);
	GraphicsDevice.ReleaseSprite(this->judgeSp_);
	GraphicsDevice.ReleaseSprite(this->numberSp_);
	GraphicsDevice.ReleaseSprite(this->growSp_);
	GraphicsDevice.ReleaseSprite(this->thankStrSp_);
	GraphicsDevice.ReleaseSprite(this->thankGrowSp_);
	this->fade_.ReleaseRenderTarget();

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

	this->AlphaChange();

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT)
		return GAME_SCENE(new TitleScene);

	if (this->fade_.GetType() == FadeInOut::FADE_OUT) return 0;

	RawInputMouse leftMouse = MultiMouse.GetInputData(0);
	RawInputMouse rightMouse = MultiMouse.GetInputData(1);

	//タイトル戻るフェード

	if (leftMouse.IsPushed(LEFTBUTTON) || rightMouse.IsPushed(LEFTBUTTON))
	{
		this->fade_.ChangeFade(FadeInOut::FADE_OUT,1000);
	}
	this->elapsedTime_ += GameTimer.GetElapsedMilliSecond();
	
	if (this->elapsedTime_ > 10000) this->fade_.ChangeFade(FadeInOut::FADE_OUT, 1000);


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
	SpriteBatch.Draw(*result_image, Vector3(0.0f, 0.0f, 0.0f),1.0f);

	for (int i = 0; i < 3;i++){
		{
			Rect useRect = RectWH(0,60 * i,280,60);
			Vector3 drawPos = Vector3(100.0f, 450.0f + 80.0f * i, 0.0f);
			SpriteBatch.Draw(*this->judgeSp_,drawPos,useRect,1.0f);
			drawPos.x += 280.0f + 30.0f;
			drawPos.y -= 2.0f;
			int value = this->counter_.perfect;
			if (i == 1) value = this->counter_.great;
			if (i == 2) value = this->counter_.miss;
			this->drawNumber_.Draw(this->numberSp_, drawPos, Vector2(87.0f, 124.0f), 0.5f, value);
			this->drawNumber_.Draw(this->growSp_, drawPos, Vector2(87.0f, 124.0f), 0.5f, value);
		}
	}

	SpriteBatch.Draw(*this->scoreSp_,Vector3(440.0f + (640.0f - 200.0f) / 2.0f,460.0f,0.0f));
	this->drawNumber_.Draw(this->numberSp_,Vector3(440.0f + (640.0f - 200.0f) / 2.0f,545.0f,0.0f), Vector2(87.0f, 124.0f), 1.0f, this->score_);

	SpriteBatch.Draw(*this->thankStrSp_,Vector3_Up * 50.0f);
	SpriteBatch.Draw(*this->thankGrowSp_,Vector3_Up * 50.0f,this->stringAlpha_);


	GraphicsDevice.ClearZBuffer();
	this->fade_.Draw();

	SpriteBatch.End();
	GraphicsDevice.EndScene();

}

void ResultScene::AlphaChange(){

	float movement = 0.02f;

	switch (this->alpha_state_){
	case ALPHA_STATE::UP:

		this->stringAlpha_ += movement;
		if (this->stringAlpha_ >= 1.0f){
			this->stringAlpha_ = 1.0f;
			this->alpha_state_ = DOWN;
		}

		break;
	case ALPHA_STATE::DOWN:
		this->stringAlpha_ -= movement;
		if (this->stringAlpha_ <= 0.5f){
			this->stringAlpha_ = 0.5f;
			this->alpha_state_ = UP;
		}

		break;
	}

}