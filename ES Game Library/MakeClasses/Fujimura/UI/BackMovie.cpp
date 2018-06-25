#include "BackMovie.h"

BackMovie::BackMovie(){

	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚P.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚Q.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚R.wmv")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("Movies/‚S.wmv")));

	for (auto movie : this->movies_){

		movie->Replay();
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

	SpriteBatch.Draw(*(*this->nowmovie_),Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,scale);

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