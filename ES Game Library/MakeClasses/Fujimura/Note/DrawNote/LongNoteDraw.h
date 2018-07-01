#pragma once
#include "DrawNote.h"

class LongNoteDraw : public DrawNote{

public:

	LongNoteDraw();
	~LongNoteDraw();

	virtual void NoteDraw(Note* note, BaseLane* lane, LONG nowTime, LONG drawRangeTime);

};