#pragma once
#include "../../ESGLib.h"

class HeartBeam;

class Dancer{

public:

	Dancer();
	~Dancer();

	void Update(DWORD nowTime);
	void Draw(DWORD nowTime);

	void SetPerformanceAnimation();
	void SetMissAnimation();

private:

	SPINE spine_;
	HeartBeam* beam_;

};