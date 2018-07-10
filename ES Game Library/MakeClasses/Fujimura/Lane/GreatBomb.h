#pragma once
#include "NoteBomb.h"

class GreatBomb : public NoteBomb{

public:

	GreatBomb();
	~GreatBomb();

	virtual void Update();
	virtual void Draw(Vector3 pos);

	virtual void ReadyBomb();

private:

	std::uniform_real_distribution<float> degreeRandom_;
	std::uniform_real_distribution<float> rotateRandom_;
	std::uniform_int_distribution<int> timeRandom_;

};