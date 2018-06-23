#pragma once
#include "../../../../ESGLib.h"

class Note;
class LongNote;

class LongBarDraw{

public:

	LongBarDraw();
	virtual ~LongBarDraw();

	void BarDraw(Vector3 startPos,Vector3 endPos,LongNote* note);

};