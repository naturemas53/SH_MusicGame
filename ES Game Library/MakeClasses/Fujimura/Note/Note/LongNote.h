#pragma once
#include "Note.h"

class LongNote : public Note{

public:

	LongNote(LONG inTiming);
	virtual ~LongNote();

	virtual void Update(){};
	virtual void Draw(SPRITE sp, Vector3 pos);

	void Push();

	LONG GetEndTiming(){ return this->endTiming_; }
	void SetEndTiming(LONG inTiming){ this->endTiming_ = timing_; }
	bool IsPushed(){ return this->pushedFlag_; }

private:

	LONG endTiming_;
	bool pushedFlag_;

};