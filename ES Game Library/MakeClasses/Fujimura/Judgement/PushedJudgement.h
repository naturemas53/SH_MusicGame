#pragma once
#include "Judgement.h"

class PushedJudgement : public Judgement{

public:
	PushedJudgement();
	virtual ~PushedJudgement();

	virtual JudgeCounter::JUDGE Judge(Note* judgeNote);

};