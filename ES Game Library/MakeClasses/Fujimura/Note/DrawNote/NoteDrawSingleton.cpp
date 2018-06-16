#include "NoteDrawSingleton.h"
#include "SingleNoteDraw.h"

NoteDrawSingleton::NoteDrawSingleton(){

	this->drawRangeTime_ = 2000;

	this->drawComponents_[Note::SINGLENOTE] = new SingleNoteDraw();
	//this->drawComponents_[Note::LONGNOTE] = new SingleNoteDraw();
	//this->drawComponents_[Note::EVENTNOTE] = new SingleNoteDraw();

}

NoteDrawSingleton::~NoteDrawSingleton(){

	for (auto components : this->drawComponents_) delete components.second;

}

bool NoteDrawSingleton::Draw(Note* note, Lane* lane, DWORD nowTime){

	long dirTime = note->GetTiming() - (long)nowTime;
	if (dirTime > (long)this->drawRangeTime_ + 100) return false;
	
	long progressTime = (long)this->drawRangeTime_ - dirTime;
	float timeRate = (float)progressTime / (float)this->drawRangeTime_;

	Note::NOTETYPE type = note->GetType();
	this->drawComponents_[type]->NoteDraw(note,lane,timeRate);

	return true;

}