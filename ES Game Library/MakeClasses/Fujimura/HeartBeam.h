#pragma once
#include "../../ESGLib.h"
#include <vector>

class HeartBeam{

public:

	HeartBeam();
	~HeartBeam();

	void Update();
	void Draw();

	void LetsBeam();

private:

	const int DRAW_RANGE_TIME_;
	SPRITE sp_;
	Vector3 pos_;
	std::vector<int> heartsTimes_;

};