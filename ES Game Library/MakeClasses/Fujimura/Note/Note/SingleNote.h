#pragma once
#include "Note.h"

class SingleNote : public Note{

public:

	SingleNote(LONG inTiming);
	virtual ~SingleNote();

	virtual void Update(){};
	virtual void Draw(SPRITE sp, Vector3 pos);

private:
	
};