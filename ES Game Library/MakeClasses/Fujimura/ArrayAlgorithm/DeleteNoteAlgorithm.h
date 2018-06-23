#pragma once
#include "ArrayAlgorithm.h"

class DeleteNoteAlgorithm : public ArrayAlgorithm{

public:
	DeleteNoteAlgorithm(){};
	~DeleteNoteAlgorithm(){};

	virtual void Execution(std::vector<Note*>& notes, Note* note);

};