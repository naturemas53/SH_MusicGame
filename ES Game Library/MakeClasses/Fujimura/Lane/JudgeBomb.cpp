#include "JudgeBomb.h"
#include "../DataSingleton.h"

JudgeBomb::JudgeBomb(Vector3 drawPos) :
MAX_PAL_VALUE_(Data.BOMB_MAX_PAL_VALUE_){

	this->palValue_ = 0;
	this->drawPos_ = drawPos;

	this->font_ = GraphicsDevice.CreateDefaultFont();
	this->color_ = Color(255, 255, 255);

}

JudgeBomb::~JudgeBomb(){



}

void JudgeBomb::Update(){

	if (this->palValue_ >= 0) this->palValue_--;

}

void JudgeBomb::Draw(){

	if (this->palValue_ <= 0) return;

	Vector2 pos = Vector2_Zero;
	pos.x = this->drawPos_.x;
	pos.y = this->drawPos_.y;

	this->color_.A((float)this->palValue_ / (float)this->MAX_PAL_VALUE_);

	SpriteBatch.DrawString(this->font_,pos,this->color_,_T("%s"),this->judgeStr_.c_str());

}

void JudgeBomb::NoticeJudge(JUDGE judge){

	if (judge == NONE) return;

	switch (judge){
	case PERFECT:
	{
		this->judgeStr_ = L"PERFECT";
		this->color_ = Color(255,0,255);
	}break;

	case GREAT:
	{
		this->judgeStr_ = L"GREAT";
		this->color_ = Color(255, 255, 255);
	}break;

	case MISS:
	{
		this->judgeStr_ = L"MISS";
		this->color_ = Color(0, 0, 0);
	}break;
	
	}

	this->palValue_ = this->MAX_PAL_VALUE_;

}