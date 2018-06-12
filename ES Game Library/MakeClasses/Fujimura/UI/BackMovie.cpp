#include "BackMovie.h"

BackMovie::BackMovie(){

	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("")));
	this->movies_.push_back(MediaManager.CreateMediaFromFile(_T("")));

	(*this->nowmovie_)->Replay();

}

BackMovie::~BackMovie(){


}

void BackMovie::Update(){

	if ((*this->nowmovie_)->IsComplete()) (*this->nowmovie_)->Replay();

}

void BackMovie::Draw(){

	SpriteBatch.Draw(*(*this->nowmovie_),Vector3_Zero);

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