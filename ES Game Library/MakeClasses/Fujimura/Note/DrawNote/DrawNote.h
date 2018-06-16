#pragma once
#include <d3dx9.h>

class Lane;
class Note;

class DrawNote{

public:

	DrawNote(){};
	virtual ~DrawNote(){};

	virtual void NoteDraw(Note* note,Lane* lane,DWORD nowTime,DWORD drawRangeTime) = 0;

};