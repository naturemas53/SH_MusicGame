#pragma once
#include <d3dx9.h>

class Lane;
class Note;

class DrawNote{

public:

	DrawNote(){};
	virtual ~DrawNote(){};

	virtual void NoteDraw(Note* note,Lane* lane,float timeRate) = 0;

};