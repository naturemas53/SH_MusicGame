#pragma once
#include "NoteFactory.h"

class SingleNoteFactory : public NoteFactory{

public:
	SingleNoteFactory(){}
	virtual ~SingleNoteFactory(){}

	virtual Note* FactoryMethod(FILE* fp, int laneNumber, LONG timing);

};