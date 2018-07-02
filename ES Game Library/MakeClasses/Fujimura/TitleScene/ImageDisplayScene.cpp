#include "ImageDisplayScene.h"
#include "MovieDisplayScene.h"

void ImageDisplayScene::LoadResource(){
	
}

void ImageDisplayScene::ReleaseResource(){
	
}

void ImageDisplayScene::Initialize(){

	this->titleSp_ = GraphicsDevice.CreateSpriteFromFile(_T("TitleScene/back_ground.png"));
	this->time_ = 0;
	this->fade_.ChangeFade(FadeInOut::FADE_IN,500);

}

void ImageDisplayScene::Finalize(){

	GraphicsDevice.ReleaseSprite(this->titleSp_);
}

TitleDisplayScene* ImageDisplayScene::Update(){

	if (this->fade_.Update() && this->fade_.GetType() == FadeInOut::FADE_OUT){
		return &MovieDisplayScene::GetInstance();
	}

	if (this->fade_.GetType() == FadeInOut::FADE_OUT) return nullptr;

	this->time_ += GameTimer.GetElapsedMilliSecond();
	if (this->time_ > 3000) this->fade_.ChangeFade(FadeInOut::FADE_OUT,700);

	return nullptr;

}

void ImageDisplayScene::Draw(){

	SpriteBatch.Draw(*this->titleSp_,Vector3_Zero);
	this->fade_.Draw();

}