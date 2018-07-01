#include "BackMovie.h"
#include "../../yoshi/effect/Effect_Singleton.h"

BackMovie::BackMovie(){
	
	this->offscreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/1.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/2.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/3.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/4.wmv")));

	this->nowmovie_ = this->movies_.begin();

	(*this->nowmovie_)->Replay();
	
	noise_time = 0;

}

BackMovie::~BackMovie(){

	GraphicsDevice.ReleaseRenderTarget(this->offscreen_);

}

void BackMovie::Update(){

	if ((*this->nowmovie_)->IsComplete()) (*this->nowmovie_)->Replay();

	if (noise_time > 0)
	{
		noise_time--;
	}

}

void BackMovie::Draw(){

	int width = 1920;
	int height = 1080;

	//例によって付け焼刃
	Vector2 scale = Vector2( 1280.0f / (float)width , 720.0f / (float)height);

	RENDERTARGET onShaderScreen = this->offscreen_;

	GraphicsDevice.SetRenderTarget(onShaderScreen);
	GraphicsDevice.Clear(0,0,0,0);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*(*this->nowmovie_),Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,scale);
	SpriteBatch.End();

	if (this->noise_time > 0){

		std::vector<Effect_Singleton::SHADER_NAME> comands_;
		comands_.push_back(Effect_Singleton::noise);
		comands_.push_back(Effect_Singleton::scan_line);

		onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comands_, onShaderScreen);

	}
	GraphicsDevice.SetDefaultRenderTarget();
	SpriteBatch.Begin();
	SpriteBatch.Draw(*onShaderScreen,Vector3_Zero);
	SpriteBatch.End();

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

	this->noise_time = 30;
	if (this->nowmovie_ == this->movies_.begin()) return;
	this->nowmovie_ = this->movies_.begin();
	(*this->nowmovie_)->Replay();
}