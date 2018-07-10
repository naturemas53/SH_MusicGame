#include "JudgeBomb.h"
#include "../DataSingleton.h"
#include "PerfectBomb.h"
#include "GreatBomb.h"
#include "MissBomb.h"

JudgeBomb::JudgeBomb() :
MAX_PAL_VALUE_(Data.BOMB_MAX_PAL_VALUE_){

	this->palValue_ = 0;
	this->useRect_ = RectWH(0,0,0,0);
	this->rivisionPos_ = Vector3_Zero;

	this->noteBombs_[PERFECT] = new PerfectBomb();
	this->noteBombs_[GREAT] = new GreatBomb();
	this->noteBombs_[MISS] = new MissBomb();
	this->nowBomb_ = this->noteBombs_[PERFECT];

}

JudgeBomb::~JudgeBomb(){

	for(auto data : this->noteBombs_){
	
		delete data.second;

	}

}

void JudgeBomb::Update(){

	if (this->palValue_ >= 0) this->palValue_--;
	this->nowBomb_->Update();

}

void JudgeBomb::Draw(Vector3 drawPos){

	if (this->palValue_ <= 0) return;

	float alpha = ((float)this->palValue_ / (float)this->MAX_PAL_VALUE_);

	SPRITE sp = Data.judgeSp_;
	Vector2 noteSize = Data.NOTESIZE_;
	Vector3 bombPos = drawPos + Vector3(noteSize.x / 2.0f,0.0f,0.0f);
	this->nowBomb_->Draw(bombPos);
	SpriteBatch.Draw(*sp,drawPos + this->rivisionPos_,this->useRect_,alpha);

}

void JudgeBomb::NoticeJudge(JUDGE judge){

	if (judge == NONE) return;

	switch (judge){
	case PERFECT:
	{
		float revisionX = (280.0f - Data.NOTESIZE_.x) / 2.5f;
		this->useRect_ = RectWH(0,0,280,60);
		this->rivisionPos_ = Vector3(-revisionX,60.0f , 0.0f);

	}break;

	case GREAT:
	{
		float revisionX = (180.0f - Data.NOTESIZE_.x) / 3.0f;
		this->useRect_ = RectWH(0, 60, 280, 60);
		this->rivisionPos_ = Vector3(-revisionX, 60.0f, 0.0f);

	}break;

	case MISS:
	{
		float revisionX = (160.0f - Data.NOTESIZE_.x) / 3.0f;
		this->useRect_ = RectWH(0, 120, 280, 60);
		this->rivisionPos_ = Vector3(-revisionX, 60.0f, 0.0f);
	}break;
	
	}
	this->palValue_ = this->MAX_PAL_VALUE_;

	auto itr = this->noteBombs_.find(judge);
	if(itr == this->noteBombs_.end()) return;

	this->nowBomb_ = itr->second;
	this->nowBomb_->ReadyBomb();

}