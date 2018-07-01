#pragma once
#include "JudgeEnum.h"
#include "JudgeResposibility\JudgeResponsib.h"
#include "JudgeResposibility\JudgeResponsibFactory.h"
#include "../RawInputMouse.h"

class Note;

class Judgement{

public:
	virtual ~Judgement(){
	
		if (this->judgeResponsib_ != nullptr){
			JudgeResponsibFactory().ReleaseTopResponsibToChain(this->judgeResponsib_);
			this->judgeResponsib_ = nullptr;
		}

	};

	virtual JUDGE Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse) = 0;

protected:

	Judgement(){
	
		if (Judgement::judgeResponsib_ == nullptr){
			this->judgeResponsib_ = JudgeResponsibFactory().CreateJudgeResponsib();
		}
	
	};
	static JudgeResponsib* judgeResponsib_;

};