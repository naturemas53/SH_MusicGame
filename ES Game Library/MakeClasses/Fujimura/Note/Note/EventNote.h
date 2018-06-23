#pragma once
#include "Note.h"

class EventNote : public Note{

public:

	EventNote(LONG inTiming);
	virtual ~EventNote();

	virtual void Update();
	virtual void Draw(SPRITE sp,Vector3 pos);

private:

};