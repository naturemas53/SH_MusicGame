#pragma once
#include "../../../../ESGLib.h"

class Note;

class NoteFactory{

public:

	virtual ~NoteFactory();

	virtual Note* Create(FILE* fp, int laneNumber, LONG timing) final{

		return this->FactoryMethod(fp,laneNumber,timing);

	}

protected:
	NoteFactory(){};

	virtual Note* FactoryMethod(FILE* fp, int laneNumber, LONG timing) = 0;

};