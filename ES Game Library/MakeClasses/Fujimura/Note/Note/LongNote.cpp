#include "LongNote.h"

LongNote::LongNote(LONG inTiming) : Note(inTiming,LONGNOTE){

	this->pushedFlag_ = false;

}

LongNote::~LongNote(){
	
}

void LongNote::Push(){ this->pushedFlag_ = true; }