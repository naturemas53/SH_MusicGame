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

	GraphicsDevice.ReleaseRenderTarget(this->offScreen_);

}

bool FadeInOut::Update(){



}

void FadeInOut::Draw(){

	SpriteBatch.Draw(*this->offScreen_,Vector3_Zero,this->alpha_);

}