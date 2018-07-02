#include "WhiteMap.h"

WhiteMap::WhiteMap() : ALPHA_DOWN_TIME_(1500){

	this->sp_ = GraphicsDevice.CreateSpriteFromFile(_T("whitecircle.png"));

	std::pair<float, int> pair;
	pair.first = 0.0f;
	pair.second = 0;
	this->scaleAnimations_.push_back(pair);
	pair.first = 0.2f;
	pair.second = 100;
	this->scaleAnimations_.push_back(pair);
	pair.first = 0.4f;
	pair.second = 1100;
	this->scaleAnimations_.push_back(pair);
	pair.first = 50.0f;
	pair.second = 2000;
	this->scaleAnimations_.push_back(pair);

	this->Reset();

}

WhiteMap::~WhiteMap(){

}

void WhiteMap::Update(){

	this->prevState_ = this->state_;
	if (this->state_ == STATE::NONE) return;

	this->time_ += GameTimer.GetElapsedMilliSecond();

	switch (this->state_){
	case STATE::SCALE_UP:
		this->ScaleUpUpdate();
		break;

	case STATE::ALPHA_DOWN:
		this->AlphaDownUpdate();
		break;
	}

}

void WhiteMap::Draw(){

	if (this->state_ == STATE::NONE) return;

	SpriteBatch.Draw(*this->sp_,Vector3((1280.0f - 720.0f) / 2.0f,0.0f,0.0f),this->alpha_,Vector3_Zero,
		Vector3(720.0f / 2.0f, 720.0f / 2.0f,0.0f),scale_);

}

void WhiteMap::Start(){

	this->state_ = STATE::SCALE_UP;
	this->prevState_ = STATE::SCALE_UP;
	this->nowPosition_ = this->scaleAnimations_.begin();

}

void WhiteMap::Reset(){

	this->state_ = STATE::NONE;
	this->prevState_ = STATE::NONE;
	this->nowPosition_ = this->scaleAnimations_.begin();
	this->alpha_ = 1.0f;
	this->scale_ = this->nowPosition_->first;
	this->time_ = 0;

}

bool WhiteMap::IsChangedState(){ return this->state_ != this->prevState_; }

void WhiteMap::ScaleUpUpdate(){

	auto s_itr = this->nowPosition_;
	auto e_itr = this->nowPosition_ + 1;

	if (this->time_ >= e_itr->second){
		this->nowPosition_++;
		s_itr++;
		e_itr++;
	}

	auto itr = this->scaleAnimations_.end();
	itr--;
	if (this->nowPosition_ == itr){
		this->state_ = STATE::ALPHA_DOWN;
		this->time_ = 0;
		return;
	}

	int dirTime = e_itr->second - s_itr->second;
	float timeRate = (float) (this->time_ - s_itr->second) / (float)dirTime;

	float dirScale = e_itr->first - s_itr->first;
	this->scale_ = s_itr->first + timeRate * dirScale;

}

void WhiteMap::AlphaDownUpdate(){

	float timeRate = (float)(this->time_) / (float)this->ALPHA_DOWN_TIME_;
	this->alpha_ = 1.0f - timeRate;

	if (this->alpha_ <= 0.0f) {
		this->Reset();
	}
}