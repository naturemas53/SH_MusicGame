#pragma once
#include "../../../../ESGLib.h"
#include "../../DataSingleton.h"

class Note {

public:

	enum NOTETYPE{

		SINGLENOTE,
		LONGNOTE,
		EVENTNOTE

	};

	Note(LONG inTiming,NOTETYPE type) : SIZE_(Data.NOTESIZE_){ 
		this->timing_ = inTiming; 
		this->type_ = type;
		this->otherTimingSameFlag_ = false;
	};
	virtual ~Note(){};

	virtual void Update() = 0;
	virtual void Draw(SPRITE sp,Vector3 pos) = 0;

	void NoticeOtherTimingSame(){ this->otherTimingSameFlag_ = true; }

	Vector2 GetSize(){ return this->SIZE_; }
	LONG GetTiming(){ return this->timing_;}
	NOTETYPE GetType(){ return this->type_; }
	bool IsOtherTimingSame(){ return this->otherTimingSameFlag_; }

protected:

	const Vector2 SIZE_;

	LONG timing_;
	NOTETYPE type_;
	bool otherTimingSameFlag_;

};