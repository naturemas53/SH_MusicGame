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

	float spWidth = sp->GetWidth();
	float spHeight = 73.0f;

	Vector2 scale = Vector2_Zero;
	scale.x = this->SIZE_.x / spWidth;
	scale.y = this->SIZE_.y / spHeight;

	SpriteBatch.Draw(*sp, pos, 1.0f, Vector3_Zero, Vector3(spWidth / 2.0f, spHeight / 2.0f, 0.0f), scale);

}

void LongNote::DrawBar(SPRITE sp, Vector3 drawPos,float angle, float hypotenuse){

	this->bar_->Draw(sp,drawPos,this->SIZE_,angle,hypotenuse);

}