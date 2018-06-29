#include "Dancer.h"
#include "HeartBeam.h"

Dancer::Dancer(){

	this->spine_ = SpineSingleton.CreateSpineFromFile("usakyara2","usakyara2",0.5f);
	this->spine_->SetPosition(Vector2(640.0f,520.0f));

	this->spine_->FlipY();
	this->spine_->SetAnimation(0,"animation",1);

	this->beam_ = new HeartBeam();
}

Dancer::~Dancer(){

	SpineSingleton.ReleaseSpine(this->spine_);
	SpineSingleton.ReleaseSpineResouse("usakyara2");

	delete this->beam_;

}

void Dancer::Update(DWORD nowTime){

	SpriteBatch.Begin();
	this->beam_->Update();
	SpriteBatch.End();

	this->spine_->Update();

}

void Dancer::Draw(DWORD nowTime){

	this->beam_->Draw();
	this->spine_->Draw();

}

void Dancer::SetPerformanceAnimation(){

	this->beam_->LetsBeam();

}

void Dancer::SetMissAnimation(){

	int a = 191919419;

}