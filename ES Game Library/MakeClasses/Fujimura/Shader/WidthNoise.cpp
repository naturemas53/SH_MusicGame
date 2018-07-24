/**
* @file WidthNoise.cpp
* @brief 横ノイズエフェクト　実装部
* @author So Fujimura
* @date 2018/07/20
*/
#include "WidthNoise.h"

WidthNoise::WidthNoise(){
	this->time_ = 0.0f;
}

WidthNoise::~WidthNoise(){


}

bool WidthNoise::Initialize(){

	Viewport view = GraphicsDevice.GetViewport();
	this->offScreen_ = GraphicsDevice.CreateRenderTarget(view.Width, view.Height, PixelFormat_RGBA8888, DepthFormat_Unknown);

	std::random_device seed;
	this->random_ = std::mt19937(seed());
	this->widthDist_ = std::uniform_real_distribution<float>(0.0f, view.Width);
	this->topHeightDist_ = std::uniform_real_distribution<float>(view.Height / 4, view.Height / 2);
	this->bottomHeightDist_ = std::uniform_real_distribution<float>(view.Height / 2, view.Height * 0.75f);
	this->persentDist_ = std::uniform_real_distribution<float>(0.0f,100.0f);

	return true;
}

void WidthNoise::Update(){

	this->time_ += 1.0f;

}

RENDERTARGET WidthNoise::Go_Shader(RENDERTARGET srcRT){

	GraphicsDevice.SetRenderTarget(this->offScreen_);
	GraphicsDevice.Clear(Color(0,0,0,0));
	
	if (srcRT->GetWidth() != this->offScreen_->GetWidth()) return srcRT;

	SpriteBatch.Begin();

	int top = this->topHeightDist_(this->random_);
	int bottom = this->bottomHeightDist_(this->random_);

	int noiseLine = 5;

	int screenHeight = (int)this->offScreen_->GetHeight();
	for (int i = 0; i < this->offScreen_->GetHeight(); i += noiseLine){

		float XPos = 0.0f;
		if (this->persentDist_(random_) <= 20.0f){
			XPos = this->widthDist_(this->random_);
		}
		Rect userect = RectWH(0, i, this->offScreen_->GetWidth(), noiseLine);
		SpriteBatch.Draw(*srcRT, Vector3(XPos, i, 0.0f), userect);
		SpriteBatch.Draw(*srcRT, Vector3(XPos - this->offScreen_->GetWidth(), i, 0.0f), userect);

	}

	SpriteBatch.End();

	GraphicsDevice.SetDefaultRenderTarget();
	
	return this->offScreen_;

}

void WidthNoise::SetParameter(std::string parameter, float value){


}