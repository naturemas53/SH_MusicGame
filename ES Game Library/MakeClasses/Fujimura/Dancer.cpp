#include "Dancer.h"

Dancer::Dancer(){

	this->spine_ = SpineSingleton.CreateSpineFromFile("Yui_Spine","skeleton",0.6f);
	this->spine_->SetPosition(Vector2(640.0f,320.0f));

	this->spine_->FlipY();
	this->spine_->SetAnimation(0,"animation",1);
}

Dancer::~Dancer(){

	SpineSingleton.ReleaseSpine(this->spine_);
	SpineSingleton.ReleaseSpineResouse("skeleton");

}

void Dancer::Update(DWORD nowTime){

	this->spine_->Update();

}

void Dancer::Draw(DWORD nowTime){

	this->spine_->Draw();

}

void Dancer::SetPerformanceAnimation(){



}

void Dancer::SetMissAnimation(){



}