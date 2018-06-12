#include "SingleNoteJudgement.h"
#include "../Note/Note/SingleNote.h"
#include <math.h>

JUDGE SingleNoteJudgement::Judge(Note* note,int nowTime){

	if (note->GetType() != Note::SINGLENOTE) return MISS;
	return this->judgeResponsib_->Judge(labs(nowTime - note->GetTiming()));

}