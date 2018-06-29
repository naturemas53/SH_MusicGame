#include "JudgeBomb.h"
#include "../DataSingleton.h"

JudgeBomb::JudgeBomb() :
MAX_PAL_VALUE_(Data.BOMB_MAX_PAL_VALUE_){

	this->palValue_ = 0;
	this->useRect_ = RectWH(0,0,0,0);

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

	SpriteBatch.Draw(*sp,drawPos,this->useRect_,alpha);

}

void JudgeBomb::NoticeJudge(JUDGE judge){

	if (judge == NONE) return;

	switch (judge){
	case PERFECT:
	{
		this->useRect_ = RectWH(0,0,280,60);
	}break;

	case GREAT:
	{
		this->useRect_ = RectWH(0, 60, 280, 60);
	}break;

	case MISS:
	{
		this->useRect_ = RectWH(0, 120, 280, 60);
	}break;
	
	}

	this->palValue_ = this->MAX_PAL_VALUE_;

}