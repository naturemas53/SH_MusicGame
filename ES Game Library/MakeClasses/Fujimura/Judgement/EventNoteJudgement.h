#pragma once
#include "Judgement.h"

class EventNoteJudgement : public Judgement{

public:

	EventNoteJudgement();
	~EventNoteJudgement();

	virtual JUDGE Judge(Note* judgeNote, DWORD nowTime, RawInputMouse& mouse);

private:

	enum MOVESTATE{

		NONE,
		MOVE_UP,
		MOVE_DOWN

	}moveState_;

	int totalMoveValue_;
	long remainMoveLimit_;

};