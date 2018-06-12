#pragma once
#include "../../../../ESGLib.h"

class Note {

public:

	enum NOTETYPE{

		SINGLENOTE,
		LONGNOTE,
		EVENTNOTE

	};

	Note(LONG inTiming,NOTETYPE type){ 
		this->timing_ = inTiming; 
		this->type_ = type;
	};
	virtual ~Note(){};

	virtual void Update() = 0;
	virtual void Draw(SPRITE sp,Vector3 pos) = 0;

	Vector2 GetSize(){ return Vector2(64.0f,32.0f); }
	LONG GetTiming(){ return this->timing_;}
	NOTETYPE GetType(){ return this->type_; }

protected:

	LONG timing_;
	NOTETYPE type_;

};