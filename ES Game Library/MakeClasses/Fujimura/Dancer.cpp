#include "Dancer.h"
#include "HeartBeam.h"

Dancer::Dancer(){

	this->spine_ = SpineSingleton.CreateSpineFromFile("usakyara2","usakyara2",0.5f);
	this->spine_->SetPosition(Vector2(660.0f,480.0f));

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

	this->beam_->Update();
	

	this->spine_->Update();

}

void Dancer::Draw(DWORD nowTime){

	SpriteBatch.Begin();
	this->beam_->Draw();
	SpriteBatch.End();
	this->spine_->Draw();

//	GraphicsDevice.ClearStencil();
	GraphicsDevice.ClearZBuffer();
}

void Dancer::SetPerformanceAnimation(){

	this->beam_->LetsBeam();

}

void Dancer::SetMissAnimation(){

	int a = 191919419;

}