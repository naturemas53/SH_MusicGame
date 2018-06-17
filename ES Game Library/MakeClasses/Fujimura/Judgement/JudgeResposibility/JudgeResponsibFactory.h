#pragma once
#include "JudgeResponsib.h"
#include <vector>

class JudgeResponsibFactory{

public:
	JudgeResponsibFactory(){};
	~JudgeResponsibFactory(){};

	JudgeResponsib* CreateJudgeResponsib(){

		JudgeResponsib* responsib = new JudgeResponsib(PERFECT);
		responsib->SetNext(new JudgeResponsib(GREAT))
				->SetNext(new JudgeResponsib(MISS));

		return responsib;

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