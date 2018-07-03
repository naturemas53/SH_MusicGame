#include "ImageDisplayScene.h"
#include "MovieDisplayScene.h"

void ImageDisplayScene::LoadResource(){
	
}

void ImageDisplayScene::ReleaseResource(){
	
}

void ImageDisplayScene::Initialize(){

	this->titleSp_ = GraphicsDevice.CreateSpriteFromFile(_T("TitleScene/back_ground.png"));
	this->clickStrSp_ = GraphicsDevice.CreateSpriteFromFile(_T("TitleScene/cleck_to_start.png"));
	this->time_ = 0;
	this->fade_.ChangeFade(FadeInOut::FADE_IN,500);
	this->stringAlpha_ = 0.0f;
	this->alpha_state_ = UP;

}

void ImageDisplayScene::Finalize(){

	GraphicsDevice.ReleaseSprite(this->titleSp_);
	GraphicsDevice.ReleaseSprite(this->clickStrSp_);
}

TitleDisplayScene* ImageDisplayScene::Update(){

	this->AlphaChange();

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT){
		return &MovieDisplayScene::GetInstance();
	}

	if (this->fade_.GetType() == FadeInOut::FADE_OUT) return nullptr;

	this->time_ += GameTimer.GetElapsedMilliSecond();
	if (this->time_ > 15000) this->fade_.ChangeFade(FadeInOut::FADE_OUT,700);

	return nullptr;

}

void ImageDisplayScene::Draw(){


	SpriteBatch.Draw(*this->titleSp_,Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,1.0f);
	SpriteBatch.Draw(*this->clickStrSp_,Vector3(200.0f, 720.0f - 210.0f,0.0f),this->stringAlpha_);
	this->fade_.Draw();

}

void ImageDisplayScene::AlphaChange(){

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
		if (this->stringAlpha_ <= 0.0f){
			this->stringAlpha_ = 0.0f;
			this->alpha_state_ = UP;
		}

		break;
	}

}