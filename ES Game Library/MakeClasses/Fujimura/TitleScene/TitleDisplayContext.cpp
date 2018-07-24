#include "TitleDisplayContext.h"
#include "ImageDisplayScene.h"
#include "MovieDisplayScene.h"

TitleDisplayContext::TitleDisplayContext(){

}

TitleDisplayContext::~TitleDisplayContext(){

	this->scene_->Finalize();
}

void TitleDisplayContext::Initialize(){

	ImageDisplayScene::GetInstance().LoadResource();
	MovieDisplayScene::GetInstance().LoadResource();

	this->scene_ = &ImageDisplayScene::GetInstance();
	this->scene_->Initialize();

}

void TitleDisplayContext::Finalize(){

	ImageDisplayScene::GetInstance().ReleaseResource();
	MovieDisplayScene::GetInstance().ReleaseResource();

}

void TitleDisplayContext::Update(){

	TitleDisplayScene* nextScene = this->scene_->Update();

	if (nextScene == nullptr) return;

	this->scene_->Finalize();
	this->scene_ = nextScene;
	this->scene_->Initialize();

}

void TitleDisplayContext::Draw(){ this->scene_->Draw(); }