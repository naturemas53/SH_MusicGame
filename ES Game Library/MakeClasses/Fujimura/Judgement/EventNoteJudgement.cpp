#include "EventNoteJudgement.h"
#include "../Note/Note/EventNote.h"
#include "../MultiMouseDevice.h"

EventNoteJudgement::EventNoteJudgement(){

	this->mouseDetections_.push_back(MouseMotionDetection());
	this->mouseDetections_.push_back(MouseMotionDetection());

	this->DetectionInitialize();

	this->remainMoveLimit_ = -2000;

}

EventNoteJudgement::~EventNoteJudgement(){



}

JUDGE EventNoteJudgement::Judge(Note* note, DWORD nowTime, RawInputMouse& mouse){

	if (note->GetType() != Note::EVENTNOTE) return MISS;

	long dirTime = note->GetTiming() - nowTime;
	if (this->remainMoveLimit_ > dirTime){
		this->DetectionInitialize();
		return MISS;
	}

	RawInputMouse& leftMouse = MultiMouse.GetInputData(0);
	RawInputMouse& rightMouse = MultiMouse.GetInputData(1);

	if (this->MoveCheck(this->mouseDetections_[0], leftMouse) && this->MoveCheck(this->mouseDetections_[1], rightMouse) ){

		this->DetectionInitialize();
		return JUDGE::PERFECT;

	}


	return JUDGE::NONE;

}

void EventNoteJudgement::DetectionInitialize(){

	this->mouseDetections_[0].SetState(MouseMotionDetection::MOVE_UP, 30);
	this->mouseDetections_[1].SetState(MouseMotionDetection::MOVE_UP, 30);

}

bool EventNoteJudgement::MoveCheck(MouseMotionDetection& detection, RawInputMouse& mouse){

	bool completedFlag = detection.Update(mouse);

	if (!completedFlag) return false;
	
	if (detection.GetState() == MouseMotionDetection::MOVE_UP){
		detection.SetState(MouseMotionDetection::MOVE_DOWN,5);
		return false;
	}

	return true;

}