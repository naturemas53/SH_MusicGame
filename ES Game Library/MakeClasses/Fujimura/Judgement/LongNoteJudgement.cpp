#include "LongNoteJudgement.h"
#include "SingleNoteJudgement.h"
#include "../Note/Note/LongNote.h"
#include "../DataSingleton.h"

LongNoteJudgement::LongNoteJudgement() :
OK_RELEASE_TIME_(Data.LONG_OK_RELEASE_TIME_)
{

	this->releaseTime_ = 0;

}

LongNoteJudgement::~LongNoteJudgement(){



}

JUDGE LongNoteJudgement::Judge(Note* judgeNote, DWORD nowTime, RawInputMouse& mouse){

	if (judgeNote->GetType() != Note::LONGNOTE)  return MISS;

	LongNote* longNote = (LongNote*)judgeNote;
	int wheelValue = mouse.GetWheelValue();

	if (!longNote->IsPushed()){
		long dirTime = (long)nowTime - (long)longNote->GetTiming();
		if (dirTime > (long)JUDGE::MISS) return MISS;

		JUDGE result = NONE;
		if (wheelValue != 0){ result = this->judgeResponsib_->Judge(labs(dirTime)); }
		if (result == MISS) return MISS;
		if (result != NONE) {

			longNote->Push();
			this->releaseTime_ = 0;

		}

		return NONE;
	}

	this->releaseTime_++;
	if (wheelValue != 0){ this->releaseTime_ = 0; }
	if (this->releaseTime_ >= this->OK_RELEASE_TIME_) return MISS;

	if (longNote->GetEndTiming() <= nowTime) return PERFECT;

	return NONE;

}