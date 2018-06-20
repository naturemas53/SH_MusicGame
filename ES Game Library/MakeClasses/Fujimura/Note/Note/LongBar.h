#pragma once
#include "../../../../ESGLib.h"

class LongBar{

public:
	LongBar();
	~LongBar();

	void Update();
	void Draw(SPRITE sp,Vector3 drawPos,Vector2 noteSize, float angle, float hypotenuse);

private:

	const int MAX_LIGHT_VALUE_;
	int nowLightValue_;

};