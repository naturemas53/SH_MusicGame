#pragma once
#include "JudgeCounter.h"
#include "JudgeResposibility\JudgeResponsib.h"
#include "JudgeResposibility\JudgeResponsibFactory.h"

class Note;

class Judgement{

public:
	virtual ~Judgement(){
	
		if (this->judgeResponsib_ != nullptr){
			JudgeResponsibFactory().ReleaseTopResponsibToChain(this->judgeResponsib_);
			this->judgeResponsib_ = nullptr;
		}

	};

	virtual JudgeCounter::JUDGE Judge(Note* judgeNote) = 0;

protected:

	Judgement(){
	
		if (Judgement::judgeResponsib_ == nullptr){
			this->judgeResponsib_ = JudgeResponsibFactory().CreateJudgeResponsib();
		}
	
	};
	static JudgeResponsib* judgeResponsib_;

};