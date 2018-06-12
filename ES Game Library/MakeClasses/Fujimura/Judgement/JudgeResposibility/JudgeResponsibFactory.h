#pragma once
#include "JudgeResponsib.h"
#include <vector>

class JudgeResponsibFactory{

public:
	JudgeResponsibFactory(){};
	~JudgeResponsibFactory(){};

	JudgeResponsib* CreateJudgeResponsib(){

		return (new JudgeResponsib(JudgeCounter::PERFECT))
				->SetNext(new JudgeResponsib(JudgeCounter::GREAT))
				->SetNext(new JudgeResponsib(JudgeCounter::MISS));

	}

	void ReleaseTopResponsibToChain(JudgeResponsib* topResponsib){

		std::vector<JudgeResponsib*> instances;
		JudgeResponsib* havenext = topResponsib;
		do{
			instances.push_back(havenext);
			havenext = havenext->GetHaveNext();
			if (havenext == nullptr) break;
		} while (true);

		for (auto responsib : instances) delete responsib;

	}

};