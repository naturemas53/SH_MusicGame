#include "JudgeBomb.h"
#include "../DataSingleton.h"

JudgeBomb::JudgeBomb() :
MAX_PAL_VALUE_(Data.BOMB_MAX_PAL_VALUE_){

	this->palValue_ = 0;
	this->useRect_ = RectWH(0,0,0,0);
	this->rivisionPos_ = Vector3_Zero;

}

JudgeBomb::~JudgeBomb(){



}

void JudgeBomb::Update(){

	if (this->palValue_ >= 0) this->palValue_--;

}

void JudgeBomb::Draw(Vector3 drawPos){

	if (this->palValue_ <= 0) return;

	float alpha = ((float)this->palValue_ / (float)this->MAX_PAL_VALUE_);

	SPRITE sp = Data.judgeSp_;

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

}