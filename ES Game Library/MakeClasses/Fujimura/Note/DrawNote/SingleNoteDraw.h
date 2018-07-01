#pragma once
#include "DrawNote.h"

class SingleNoteDraw : public DrawNote{

public:

	SingleNoteDraw();
	virtual ~SingleNoteDraw();

	virtual void NoteDraw(Note* note, BaseLane* lane, LONG nowTime, LONG drawRangeTime);

};