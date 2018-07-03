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

	SPINE sideStepSpine_;
	SPINE heartSpine_;
	SPINE drawSpine_;

	HeartBeam* beam_;

};