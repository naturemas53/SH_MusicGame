#pragma once
#include "MouseMotionDetection.h"

class DetectMultiMotion{

public:

	typedef std::pair<MouseMotionDetection::MOVESTATE, int> MOVESET;

	DetectMultiMotion();
	~DetectMultiMotion();

	void Initialize();
	bool Update(RawInputMouse& mouse);
	void AddNormSet(MOVESET addSet);

private:

	std::vector<MOVESET> normMoves_;
	std::vector<MOVESET>::iterator nowNorm_;
	MouseMotionDetection mouseDetection_;

};