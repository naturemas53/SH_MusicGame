#pragma once
#include "../../ESGLib.h"

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


};