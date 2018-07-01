#include "SingleNoteJudgement.h"
#include "../Note/Note/SingleNote.h"
#include <math.h>

JUDGE SingleNoteJudgement::Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse){

	if (judgeNote->GetType() != Note::SINGLENOTE) return MISS;

	long dirTime = (long)nowTime - (long)judgeNote->GetTiming();
	if (dirTime > (long)JUDGE::MISS) return MISS;

	if (mouse.IsPushed(LEFTBUTTON) || mouse.IsPushed(RIGHTBUTTON)){
		return Judgement::judgeResponsib_->Judge(labs(nowTime - judgeNote->GetTiming()));
	}

	return NONE;

}