#pragma once
#include "../../ESGLib.h"
#include "Judgement\JudgeEnum.h"
#include <vector>

class ClapSingleton{

public:
	static ClapSingleton& GetInstance(){

		static ClapSingleton instance;
		return instance;

	}

	~ClapSingleton();

	void LoadClap();

	void PlayClap(JUDGE judge);
	void PlayEventClap(JUDGE judge);

private:

	ClapSingleton();

	std::map<JUDGE, SOUND> clapSounds_;
	std::map<JUDGE, SOUND> eventClapSounds_;

};

#define ClapManager ClapSingleton::GetInstance()