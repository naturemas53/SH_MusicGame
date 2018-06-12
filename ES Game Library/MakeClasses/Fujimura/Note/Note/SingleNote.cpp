#include "SingleNote.h"

SingleNote::SingleNote(LONG inTiming) : Note(inTiming){



}

SingleNote::~SingleNote(){


}

void SingleNote::Draw(SPRITE sp,Vector3 pos){

	SpriteBatch.Draw(*sp,pos);

}