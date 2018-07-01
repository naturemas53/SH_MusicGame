#include "EventNoteJudgement.h"
#include "../Note/Note/EventNote.h"
#include "../MultiMouseDevice.h"

EventNoteJudgement::EventNoteJudgement(){

	this->mouseDetections_.push_back(DetectMultiMotion());
	this->mouseDetections_.push_back(DetectMultiMotion());

	DetectMultiMotion::MOVESET set;
	set.first = MouseMotionDetection::MOVE_UP;
	set.second = 30;
	this->mouseDetections_[0].AddNormSet(set);
	this->mouseDetections_[1].AddNormSet(set);

	set.first = MouseMotionDetection::MOVE_RIGHT;
	set.second = 10;
	this->mouseDetections_[0].AddNormSet(set);

	set.first = MouseMotionDetection::MOVE_LEFT;
	set.second = 10;
	this->mouseDetections_[1].AddNormSet(set);

	this->DetectionInitialize();

	this->remainMoveLimit_ = 1000;

}

EventNoteJudgement::~EventNoteJudgement(){



}

JUDGE EventNoteJudgement::Judge(Note* note, LONG nowTime, RawInputMouse& mouse){

	if (note->GetType() != Note::EVENTNOTE) return MISS;

	long dirTime = note->GetTiming() - nowTime;
	if (this->remainMoveLimit_ < dirTime) return JUDGE::NONE;
	if (dirTime < -MISS){
		this->DetectionInitialize();
		return MISS;
	}

	if (this->MoveCheck(0) && this->MoveCheck(1) ){

		this->DetectionInitialize();
		return JUDGE::PERFECT;

	}


	return JUDGE::NONE;

}

void EventNoteJudgement::DetectionInitialize(){

	for (int i = 0; i < this->mouseDetections_.size(); i++){

		this->mouseDetections_[i].Initialize();

	}

}

bool EventNoteJudgement::MoveCheck(int mousenum){

	RawInputMouse& mouse = MultiMouse.GetInputData(mousenum);

	return this->mouseDetections_[mousenum].Update(mouse);

}