#pragma once
#include "../JudgeCounter.h"

class JudgeResponsib{

public:

	explicit JudgeResponsib(JudgeCounter::JUDGE haveJudge){

		this->next_ = nullptr;
		this->havejudge_ = haveJudge;

	}

	~JudgeResponsib(){

	}

	JudgeCounter::JUDGE Judge(int absTime){

		if (absTime < this->havejudge_) return this->havejudge_;
		if (this->next_ != nullptr) return this->next_->Judge(absTime);
		return JudgeCounter::NONE;

	};

	JudgeResponsib* SetNext(JudgeResponsib* resposib){

		this->next_ = resposib;
		return resposib;

	}

	JudgeResponsib* GetHaveNext() { return this->next_; }

	JudgeResponsib* next_;
	JudgeCounter::JUDGE havejudge_;


};