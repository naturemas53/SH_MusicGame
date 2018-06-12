#pragma once
#include "../../../../ESGLib.h"

class Note {

public:

	Note(LONG inTiming){ this->timing_ = inTiming; };
	virtual ~Note(){};

	virtual void Update() = 0;
	virtual void Draw(SPRITE sp,Vector3 pos) = 0;

	Vector2 GetSize(){ return Vector2(64.0f,32.0f); }

protected:

	LONG timing_;

};