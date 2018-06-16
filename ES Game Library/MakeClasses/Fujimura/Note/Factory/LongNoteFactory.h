#pragma once
#include "NoteFactory.h"

class LongNoteFactory : public NoteFactory{

public:

	LongNoteFactory();
	~LongNoteFactory();

	virtual Note* FactoryMethod(FILE* fp, int laneNumber, LONG timing) = 0;

};