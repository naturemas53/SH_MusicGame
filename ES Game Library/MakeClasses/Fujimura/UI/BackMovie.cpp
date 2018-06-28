#include "BackMovie.h"
#include "../../yoshi/effect/Effect_Singleton.h"

BackMovie::BackMovie(){

	this->offscreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚P.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚Q.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚R.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚S.wmv")));

	for (auto movie : this->movies_){

		movie->Replay();
		SpriteBatch.Begin();
		SpriteBatch.Draw(*movie, Vector3_Zero, 1.0f);
		SpriteBatch.End();
		movie->Stop();
		
	}

	this->nowmovie_ = this->movies_.begin();

	(*this->nowmovie_)->Replay();

}

BackMovie::~BackMovie(){


}

void BackMovie::Update(){

	if ((*this->nowmovie_)->IsComplete()) (*this->nowmovie_)->Replay();

}

void BackMovie::Draw(){

	int width = (*this->nowmovie_)->GetWidth();
	int height = (*this->nowmovie_)->GetHeight();

	//—á‚É‚æ‚Á‚Ä•t‚¯Än
	Vector2 scale = Vector2( 1280.0f / (float)width , 720.0f / (float)height);

	RENDERTARGET onShaderScreen = this->offscreen_;

	GraphicsDevice.SetRenderTarget(this->offscreen_);
	GraphicsDevice.Clear(0,0,0,0);

	SpriteBatch.Begin();
	SpriteBatch.Draw(*(*this->nowmovie_),Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,scale);
	SpriteBatch.End();

	std::vector<Effect_Singleton::SHADER_NAME> commands_;
	commands_.push_back(Effect_Singleton::blur);

	//RENDERTARGET onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(commands_,this->offscreen_);

	GraphicsDevice.SetDefaultRenderTarget();

	SpriteBatch.Begin();
	SpriteBatch.InitTransform();
	SpriteBatch.DrawSimple(*onShaderScreen,Vector3_Zero);
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

	if (this->nowmovie_ == this->movies_.begin()) return;
	this->nowmovie_ = this->movies_.begin();
	(*this->nowmovie_)->Replay();
}