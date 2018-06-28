#pragma once
#include "JudgeEnum.h"

struct JudgeCounter{

	int perfect;
	int great;
	int miss;

	JudgeCounter::JudgeCounter(){

		this->perfect = 0;
		this->great = 0;
		this->miss = 0;

	}

	int GetScoreValue(){

		int value = this->perfect * 100;
		value += this->great * 50;

		return value;

	}

	JudgeCounter operator+ (const JUDGE value){

		switch (value){
		case PERFECT: this->perfect++; break;
		case GREAT: this->great++; break;
		case MISS: this->miss++; break;
		}

		return *this;

	}

	JudgeCounter operator= (const JudgeCounter value){

		this->perfect = value.perfect;
		this->great = value.great;
		this->miss = value.miss;

		return *this;

	}

};