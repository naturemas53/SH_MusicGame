#pragma once
#include "Judgement.h"

class Note;

class LongNoteJudgement : public Judgement{

public:

	LongNoteJudgement();
	~LongNoteJudgement();

	virtual JUDGE Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse);

private:

	const int OK_RELEASE_TIME_;
	int releaseTime_;

};