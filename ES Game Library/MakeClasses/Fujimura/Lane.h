#pragma once
#include "../../ESGLib.h"
#include <vector>

class Lane{

public:

	Lane(Vector3 inPos);
	~Lane();

	void Draw();

	Vector2 GetSize(){ return this->SIZE_; }

private:

	const Vector2 SIZE_;
	const Vector3 POS_;

	SPRITE sp_;

};