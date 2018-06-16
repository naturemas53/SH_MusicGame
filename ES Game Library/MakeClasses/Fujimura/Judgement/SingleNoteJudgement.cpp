#include "SingleNoteJudgement.h"
#include "../Note/Note/SingleNote.h"
#include <math.h>

JUDGE SingleNoteJudgement::Judge(Note* note, DWORD nowTime, RawInputMouse& mouse){

	if (note->GetType() != Note::SINGLENOTE) return MISS;

	long dirTime = (long)nowTime - (long)note->GetTiming();
	if (dirTime > (long)JUDGE::MISS) return MISS;

	if (mouse.IsButtonUp(LEFTBUTTON) && mouse.IsButtonUp(RIGHTBUTTON)) return NONE;

	return this->judgeResponsib_->Judge(labs(nowTime - note->GetTiming()));

}