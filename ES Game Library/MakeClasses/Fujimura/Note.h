#pragma once
#include "../../ESGLib.h"

class Note {

public:
	Note(){};
	virtual ~Note();

	virtual void Update() = 0;
	virtual void Draw() = 0;

};