#pragma once
#include "../../../ESGLib.h"
#include <vector>
#include <random>

class NoteBomb{

public:

	NoteBomb(){ 
	
		std::random_device seed;
		this->random_ = std::mt19937(seed());

		this->time_ = 0;

	};
	virtual ~NoteBomb(){};

	virtual void Update() = 0;
	virtual void Draw(Vector3 pos) = 0;

	virtual void ReadyBomb() = 0;

protected:

	struct Light{
	
		float degrees_;
		float baseRotate_;
		int time_;
		Rect rect_;
	
	};

	std::vector<Light> lights_;

	std::mt19937 random_;

	int time_;

};