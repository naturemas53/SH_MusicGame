#include "NoteDrawSingleton.h"
#include "SingleNoteDraw.h"
#include "LongNoteDraw.h"
#include "EventNoteDraw.h"

NoteDrawSingleton::NoteDrawSingleton(){

	this->drawRangeTime_ = 2000;

	this->drawComponents_[Note::SINGLENOTE] = new SingleNoteDraw();
	this->drawComponents_[Note::LONGNOTE] = new LongNoteDraw();
	this->drawComponents_[Note::EVENTNOTE] = new EventNoteDraw();

}

NoteDrawSingleton::~NoteDrawSingleton(){

	for (auto components : this->drawComponents_) delete components.second;

}

bool NoteDrawSingleton::Draw(Note* note, BaseLane* lane, LONG nowTime){

	long dirTime = note->GetTiming() - (long)nowTime;
	if (dirTime > (long) (this->drawRangeTime_ + 500) )return false;

	Note::NOTETYPE type = note->GetType();
	this->drawComponents_[type]->NoteDraw(note,lane,nowTime,this->drawRangeTime_);

	return true;

}