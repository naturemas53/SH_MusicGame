#include "BackMovie.h"
#include "../../yoshi/effect/Effect_Singleton.h"

BackMovie::BackMovie(){
	
	offscreen[0] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

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

	effect_noise = Noise();
	
	noise_time = 0;

}

BackMovie::~BackMovie(){


}

void BackMovie::Update(){

	if ((*this->nowmovie_)->IsComplete()) (*this->nowmovie_)->Replay();


	if (noise_time > 0)
	{
		noise_time--;
	}

}

void BackMovie::Draw(){
	GraphicsDevice.SetRenderTarget(offscreen[0]);
	GraphicsDevice.Clear(Color_Black);

	SpriteBatch.Begin();



	int width = (*this->nowmovie_)->GetWidth();
	int height = (*this->nowmovie_)->GetHeight();

	//—á‚É‚æ‚Á‚Ä•t‚¯Än
	Vector2 scale = Vector2( 1280.0f / (float)width , 720.0f / (float)height);

	SpriteBatch.Draw(*(*this->nowmovie_),Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,scale);
	SpriteBatch.End();

	std::vector<Effect_Singleton::SHADER_NAME> comands_;
	/*comands_.push_back(Effect_Singleton::noise);
	comands_.push_back(Effect_Singleton::scan_line);*/
	//comands_.push_back(Effect_Singleton::rester);
	//comands_.push_back(Effect_Singleton::blur);
	//comands_.push_back(Effect_Singleton::bloom);



	RENDERTARGET unko = Effect_Singleton::GetInstance().Image_On_Effect(comands_, offscreen[0]);

	//if (noise_time <= 0)
	//{
	//	unko = offscreen[0];
	//}

	GraphicsDevice.SetDefaultRenderTarget();


	GraphicsDevice.RenderTargetToBackBuffer(nullptr, unko, nullptr);


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

	noise_time = 4000;
	if (this->nowmovie_ == this->movies_.begin()) return;
	this->nowmovie_ = this->movies_.begin();
	(*this->nowmovie_)->Replay();
}