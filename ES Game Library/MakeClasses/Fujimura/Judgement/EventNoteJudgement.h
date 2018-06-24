#pragma once
#include "Judgement.h"
#include "DetectMultiMotion.h"
#include <vector>
#include <map>

class EventNoteJudgement : public Judgement{

public:

	EventNoteJudgement();
	~EventNoteJudgement();

	virtual JUDGE Judge(Note* judgeNote, DWORD nowTime, RawInputMouse& mouse);

private:
	
	void DetectionInitialize();
	bool MoveCheck(int mousenum);

	std::vector<DetectMultiMotion> mouseDetections_;
	long remainMoveLimit_;

};