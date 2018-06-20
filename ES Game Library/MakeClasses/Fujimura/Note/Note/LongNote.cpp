#include "LongNote.h"

LongNote::LongNote(LONG inTiming) : Note(inTiming,LONGNOTE){

	this->pushedFlag_ = false;
	this->bar_ = new LongBar();

}

LongNote::~LongNote(){
	delete this->bar_;
}

void LongNote::Update(){

	if (this->pushedFlag_) this->bar_->Update();

}

void LongNote::Push(){ this->pushedFlag_ = true; }

void LongNote::Draw(SPRITE sp,Vector3 pos){

	Rect useRect = RectWH(64, 80, 64, 32);
	SpriteBatch.Draw(*sp, pos, useRect);

}

void LongNote::DrawBar(SPRITE sp, Vector3 drawPos,float angle, float hypotenuse){

	this->bar_->Draw(sp,drawPos,this->SIZE_,angle,hypotenuse);

}