#pragma once
#include <d3dx9.h>

class BaseLane;
class Note;

class DrawNote{

public:

	DrawNote(){};
	virtual ~DrawNote(){};

	virtual void NoteDraw(Note* note, BaseLane* lane, LONG nowTime, LONG drawRangeTime) = 0;

};