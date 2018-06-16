#include "LongNote.h"

LongNote::LongNote(LONG inTiming) : Note(inTiming,LONGNOTE){

	this->pushedFlag_ = false;

}

LongNote::~LongNote(){
	
}

void LongNote::Push(){ this->pushedFlag_ = true; }

void LongNote::Draw(SPRITE sp,Vector3 pos){

	Rect useRect = RectWH(0, 80, 64, 64);
	SpriteBatch.Draw(*sp, pos, useRect);

}