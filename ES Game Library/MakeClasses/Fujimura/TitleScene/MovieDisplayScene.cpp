#include "MovieDisplayScene.h"
#include "ImageDisplayScene.h"

void MovieDisplayScene::LoadResource(){
	
	this->movie_ = MediaManager.CreateMediaFromFile(_T("TitleScene/demo_movie.wmv"));
	this->clickStrSp_ = GraphicsDevice.CreateSpriteFromFile(_T("TitleScene/cleck_to_start.png"));

}

void MovieDisplayScene::ReleaseResource(){
	
	MediaManager.ReleaseMedia(this->movie_);
	GraphicsDevice.ReleaseSprite(this->clickStrSp_);

}

void MovieDisplayScene::Initialize(){


	this->movie_->Replay();
	this->fade_.ChangeFade(FadeInOut::FADE_IN, 500);

	this->stringAlpha_ = 0.0f;
	this->alpha_state_ = UP;

}

void MovieDisplayScene::Finalize(){

}

TitleDisplayScene* MovieDisplayScene::Update(){

	this->AlphaChange();

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT){
		this->movie_->Stop();
		return &ImageDisplayScene::GetInstance();
	}

	if (this->fade_.GetType() == FadeInOut::FADE_OUT) return nullptr;

	REFERENCE_TIME oneSec = 10000000;
	REFERENCE_TIME timeLength = this->movie_->GetLength();
	REFERENCE_TIME nowPos = this->movie_->GetPosition();

	if (nowPos > timeLength - oneSec * 5) this->fade_.ChangeFade(FadeInOut::FADE_OUT, 700);

	return nullptr;

}

void MovieDisplayScene::Draw(){

	SpriteBatch.Draw(*this->movie_, Vector3_Zero);
	SpriteBatch.Draw(*this->clickStrSp_,Vector3((1280.0f - 369.0f) / 2.0f, 720.0f - 210.0f,0.0f),this->stringAlpha_);
	this->fade_.Draw();

}

void MovieDisplayScene::AlphaChange(){

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