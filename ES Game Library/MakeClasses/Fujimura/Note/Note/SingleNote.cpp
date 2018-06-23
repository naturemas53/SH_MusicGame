#include "SingleNote.h"

SingleNote::SingleNote(LONG inTiming) : Note(inTiming,SINGLENOTE){



}

SingleNote::~SingleNote(){


}

void SingleNote::Draw(SPRITE sp,Vector3 pos){

	float spWidth = sp->GetWidth();
	float spHeight = 73.0f;

	Vector2 scale = Vector2_Zero;
	scale.x = this->SIZE_.x / spWidth;
	scale.y = this->SIZE_.y / spHeight;

	SpriteBatch.Draw(*sp, pos,1.0f,Vector3_Zero,Vector3(spWidth / 2.0f,spHeight / 2.0f,0.0f),scale);

}