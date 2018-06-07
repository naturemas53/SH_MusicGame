#pragma once
#include "../../ESGLib.h"
#include <vector>

class Lane{

public:

	Lane();
	~Lane();

	void Update();
	void Draw();

	Vector2 GetSize(){ return this->SIZE_; }

	void AddNote(){};

private:

	const Vector2 SIZE_;
	//vector

};