#pragma once
#include "NoteFactory.h"

class EventNoteFactory : public NoteFactory{

public:

	EventNoteFactory();
	~EventNoteFactory();

	virtual Note* FactoryMethod(FILE* fp, int laneNumber, LONG timing);

private:

};