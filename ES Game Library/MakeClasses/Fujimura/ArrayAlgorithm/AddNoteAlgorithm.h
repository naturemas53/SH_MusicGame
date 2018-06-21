#pragma once
#include "ArrayAlgorithm.h"

class AddNoteAlgorithm : public ArrayAlgorithm{

public:

	AddNoteAlgorithm(){};
	~AddNoteAlgorithm(){};

	virtual void Execution(std::vector<Note*>& notes, Note* note);

};