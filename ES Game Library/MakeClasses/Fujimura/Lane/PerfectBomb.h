#pragma once
#include "NoteBomb.h"

class PerfectBomb : public NoteBomb{

public:

	PerfectBomb();
	~PerfectBomb();

	virtual void Update();
	virtual void Draw(Vector3 pos);

	virtual void ReadyBomb();

private:

	std::uniform_real_distribution<float> degreeRandom_;
	std::uniform_real_distribution<float> rotateRandom_;
	std::uniform_int_distribution<int> timeRandom_;

};