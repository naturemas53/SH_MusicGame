#include "TitleDisplayContext.h"
#include "ImageDisplayScene.h"
#include "MovieDisplayScene.h"

TitleDisplayContext::TitleDisplayContext(){

	this->scene_ = &ImageDisplayScene::GetInstance();
	this->scene_->Initialize();
}

TitleDisplayContext::~TitleDisplayContext(){

	this->scene_->Finalize();
}

void TitleDisplayContext::Update(){

	TitleDisplayScene* nextScene = this->scene_->Update();

	if (nextScene == nullptr) return;

	this->scene_->Finalize();
	this->scene_ = nextScene;
	this->scene_->Initialize();

}

void TitleDisplayContext::Draw(){ this->scene_->Draw(); }