#include "EventNoteJudgement.h"
#include "../Note/Note/EventNote.h"

EventNoteJudgement::EventNoteJudgement(){

	this->totalMoveValue_ = 0;
	this->moveState_ = NONE;
	this->remainMoveLimit_ = -2000;

}

EventNoteJudgement::~EventNoteJudgement(){



}

JUDGE EventNoteJudgement::Judge(Note* note, DWORD nowTime, RawInputMouse& mouse){

	if (note->GetType() != Note::EVENTNOTE) return MISS;

	long dirTime = note->GetTiming() - nowTime;
	if (this->remainMoveLimit_ > dirTime){
		this->totalMoveValue_ = 0;
		this->moveState_ = MOVESTATE::NONE;
		return MISS;
	}

	if (this->moveState_ == MOVESTATE::NONE) this->moveState_ = MOVE_UP;

	switch (this->moveState_){

	case MOVE_UP:
	{

		int value = mouse.GetAxisY();
		if (value > 0) this->totalMoveValue_ += value;
		if (this->totalMoveValue_ > 100){
			this->totalMoveValue_ = 0;
			this->moveState_ = MOVE_DOWN;
		}

	}
	break;

	case MOVE_DOWN:
	{

		int value = mouse.GetAxisY();
		if (value < 0) this->totalMoveValue_ += value;
		if (this->totalMoveValue_ < -20){
			this->totalMoveValue_ = 0;
			this->moveState_ = MOVESTATE::NONE;
			return PERFECT;
		}

	}break;

	default:
		break;

	}

	return JUDGE::NONE;

}