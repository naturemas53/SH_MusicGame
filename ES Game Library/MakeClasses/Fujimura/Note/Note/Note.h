#pragma once
#include "../../../../ESGLib.h"

class Note {

public:

	enum NOTETYPE{

		SINGLENOTE,
		LONGNOTE,
		EVENTNOTE

	};

	Note(LONG inTiming,NOTETYPE type) : SIZE_(Vector2(112.0f,32.0f)){ 
		this->timing_ = inTiming; 
		this->type_ = type;
	};
	virtual ~Note(){};

	virtual void Update() = 0;
	virtual void Draw(SPRITE sp,Vector3 pos) = 0;

	Vector2 GetSize(){ return this->SIZE_; }
	LONG GetTiming(){ return this->timing_;}
	NOTETYPE GetType(){ return this->type_; }

protected:

	const Vector2 SIZE_;
	LONG timing_;
	NOTETYPE type_;

};