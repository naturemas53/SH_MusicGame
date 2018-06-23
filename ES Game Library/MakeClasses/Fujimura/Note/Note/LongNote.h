#pragma once
#include "Note.h"
#include "LongBar.h"

class LongNote : public Note{

public:

	LongNote(LONG inTiming);
	virtual ~LongNote();

	virtual void Update();
	virtual void Draw(SPRITE sp, Vector3 pos);
	virtual void DrawBar(SPRITE sp, Vector3 drawPos, float angle, float hypotenuse);

	void Push();

	LONG GetEndTiming(){ return this->endTiming_; }
	void SetEndTiming(LONG inTiming){ this->endTiming_ = inTiming; }
	bool IsPushed(){ return this->pushedFlag_; }

private:

	LongBar* bar_;
	LONG endTiming_;
	bool pushedFlag_;

};