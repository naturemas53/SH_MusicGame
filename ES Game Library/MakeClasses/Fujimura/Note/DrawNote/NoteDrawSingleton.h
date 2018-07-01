#pragma once
#include <map>
#include "../Note/Note.h"

class DrawNote;
class BaseLane;

class NoteDrawSingleton{

public:

	static NoteDrawSingleton& GetInstance(){

		static NoteDrawSingleton instance;
		return instance;

	}

	~NoteDrawSingleton();

	bool Draw(Note* note, BaseLane* lane, LONG nowTime);
	void SetDrawRangeTime(LONG inTime);

private:

	NoteDrawSingleton();

	std::map<Note::NOTETYPE,DrawNote*> drawComponents_;
	LONG drawRangeTime_;

};

#define NoteDrawComponent NoteDrawSingleton::GetInstance()