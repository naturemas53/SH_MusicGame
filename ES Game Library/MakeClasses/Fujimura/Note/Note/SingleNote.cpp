#include "SingleNote.h"

SingleNote::SingleNote(LONG inTiming) : Note(inTiming,SINGLENOTE){



}

SingleNote::~SingleNote(){


}

void SingleNote::Draw(SPRITE sp,Vector3 pos){

	Rect useRect = RectWH(0,80,64,64);
	SpriteBatch.Draw(*sp, pos, useRect);

}