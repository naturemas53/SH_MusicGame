#include "BackMovie.h"


BackMovie::BackMovie(){

	offscreen[0] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚P.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚Q.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚R.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚S.wmv")));

	this->nowmovie_ = this->movies_.begin();

	(*this->nowmovie_)->Replay();

	effect_noise = Noise();
	effect_scan_line = Scan_Line();

	noise_time = 0;

}

BackMovie::~BackMovie(){


}

void BackMovie::Update(){

	if ((*this->nowmovie_)->IsComplete()) (*this->nowmovie_)->Replay();

	effect_noise.Update();
	

	if (noise_time > 0) noise_time--;

		
}

void BackMovie::Draw(){
	
	SpriteBatch.Begin();
	GraphicsDevice.SetRenderTarget(offscreen[0]);
	GraphicsDevice.Clear(Color_Black);

	/*RENDERTARGET unko2 = effect_scan_line.Go_Shader(offscreen[1]);*/


	int width = (*this->nowmovie_)->GetWidth();
	int height = (*this->nowmovie_)->GetHeight();

	//—á‚É‚æ‚Á‚Ä•t‚¯Än
	Vector2 scale = Vector2( 1280.0f / (float)width , 720.0f / (float)height);

	SpriteBatch.Draw(*(*this->nowmovie_),Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,scale);
	SpriteBatch.End();

	RENDERTARGET unko = effect_noise.Go_Shader(offscreen[0]);
	if (noise_time <= 0) unko = offscreen[0];

	GraphicsDevice.SetDefaultRenderTarget();
	GraphicsDevice.RenderTargetToBackBuffer(nullptr, unko, nullptr);
	


	
	

	//if (effect_save == 0)
	//{
	//	/*GraphicsDevice.SetRenderTarget(offscreen);*/

	//	SpriteBatch.Draw(*offscreen, Vector3(0.0f, 0.0f, 0.0f));
	//	GraphicsDevice.RenderTargetToBackBuffer(nullptr, offscreen, nullptr);
	//	
	//	//GraphicsDevice.RenderTargetToRenderTarget(offscreen[1], offscreen[0], noise_effect);
	//	//	//GraphicsDevice.SetDefaultRenderTarget();
	//}


}

void BackMovie::MovieChange(){

	this->nowmovie_++;
	if (this->nowmovie_ == this->movies_.end()) {
		this->nowmovie_--;
		return;
	}
	(*this->nowmovie_)->Replay();
}

void BackMovie::MovieReset(){ 

	noise_time = 30;
	RENDERTARGET unko = effect_noise.Go_Shader(offscreen[0]);
	if (this->nowmovie_ == this->movies_.begin()) return;
	this->nowmovie_ = this->movies_.begin();
	(*this->nowmovie_)->Replay();
}