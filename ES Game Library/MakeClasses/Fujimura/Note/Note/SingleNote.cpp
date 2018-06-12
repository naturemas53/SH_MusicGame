#include "SingleNote.h"

SingleNote::SingleNote(LONG inTiming) : Note(inTiming,SINGLENOTE){



}

SingleNote::~SingleNote(){


}

void SingleNote::Draw(SPRITE sp,Vector3 pos){

	SpriteBatch.Draw(*sp,pos);

}