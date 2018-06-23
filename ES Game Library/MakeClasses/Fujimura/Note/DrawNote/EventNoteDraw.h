#pragma once
#include "DrawNote.h"

class EventNoteDraw : public DrawNote{

public:

	EventNoteDraw();
	~EventNoteDraw();

	virtual void NoteDraw(Note* note, BaseLane* lane, DWORD nowTime, DWORD drawRangeTime);

};