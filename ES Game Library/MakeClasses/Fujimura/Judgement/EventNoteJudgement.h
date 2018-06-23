#pragma once
#include "Judgement.h"
#include "MouseMotionDetection.h"
#include <vector>

class EventNoteJudgement : public Judgement{

public:

	EventNoteJudgement();
	~EventNoteJudgement();

	virtual JUDGE Judge(Note* judgeNote, DWORD nowTime, RawInputMouse& mouse);

private:
	
	void DetectionInitialize();
	bool MoveCheck(MouseMotionDetection& detection,RawInputMouse& mouse);

	std::vector<MouseMotionDetection> mouseDetections_;
	long remainMoveLimit_;

};