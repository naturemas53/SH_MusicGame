#include "MovieDisplayScene.h"
#include "ImageDisplayScene.h"

void MovieDisplayScene::LoadResource(){
	
}

void MovieDisplayScene::ReleaseResource(){
	
}

void MovieDisplayScene::Initialize(){

	this->movie_ = MediaManager.CreateMediaFromFile(_T("TitleScene/demo_movie.wmv"));
	this->movie_->Replay();
	this->fade_.ChangeFade(FadeInOut::FADE_IN, 500);

}

void MovieDisplayScene::Finalize(){
	MediaManager.ReleaseMedia(this->movie_);
}

TitleDisplayScene* MovieDisplayScene::Update(){

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
	this->fade_.Draw();

}