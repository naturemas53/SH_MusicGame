#include "FadeInOut.h"

FadeInOut::FadeInOut(){


	this->offScreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	GraphicsDevice.SetRenderTarget(this->offScreen_);
	GraphicsDevice.Clear(Color_Black);
	GraphicsDevice.SetDefaultRenderTarget();
	this->elapsedTime_ = 0;
	this->fadeTime_ = 1000;
	this->alpha_ = 1.0f;
	this->fadetype_ = FADE_IN;

}

FadeInOut::~FadeInOut(){

}

void FadeInOut::ReleaseRenderTarget(){

	GraphicsDevice.ReleaseRenderTarget(this->offScreen_);

}

bool FadeInOut::Update(){

	int elapsedTime = GameTimer.GetElapsedMilliSecond();

	this->elapsedTime_ += elapsedTime;
	float timeRate = (float)this->elapsedTime_ / (float)this->fadeTime_;
	if (timeRate > 1.0f) timeRate = 1.0f;

	this->alpha_ = timeRate;
	if (this->fadetype_ == FADETYPE::FADE_IN) this->alpha_ = 1.0f - timeRate;

	return timeRate >= 1.0f;

}

void FadeInOut::Draw(){

	SpriteBatch.Draw(*this->offScreen_,Vector3_Zero,this->alpha_);

}

void FadeInOut::ChangeFade(FADETYPE type,int fadeTime){

	this->elapsedTime_ = 0;
	this->fadeTime_ = fadeTime;
	this->fadetype_ = type;

}