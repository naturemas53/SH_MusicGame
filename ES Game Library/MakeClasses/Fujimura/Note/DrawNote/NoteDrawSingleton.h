#pragma once
#include <map>
#include "../Note/Note.h"

class DrawNote;
class Lane;

class NoteDrawSingleton{

public:

	static NoteDrawSingleton& GetInstance(){

		static NoteDrawSingleton instance;
		return instance;

	}

	~NoteDrawSingleton();

	bool Draw(Note* note, Lane* lane,DWORD nowTime);
	void SetDrawRangeTime(DWORD inTime);

private:

	NoteDrawSingleton();

	std::map<Note::NOTETYPE,DrawNote*> drawComponents_;
	DWORD drawRangeTime_;

};

#define NoteDrawComponent NoteDrawSingleton::GetInstance()