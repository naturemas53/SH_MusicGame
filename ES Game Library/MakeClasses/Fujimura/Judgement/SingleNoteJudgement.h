#pragma once
#include "Judgement.h"

class SingleNoteJudgement : public Judgement{

public:
	SingleNoteJudgement(){};
	virtual ~SingleNoteJudgement(){};

	virtual JUDGE Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse);


};