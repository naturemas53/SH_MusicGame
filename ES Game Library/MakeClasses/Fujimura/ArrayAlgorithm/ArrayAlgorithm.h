#pragma once
#include <vector>

class Note;

class ArrayAlgorithm{

public:

	ArrayAlgorithm(){};
	~ArrayAlgorithm(){};

	virtual void Execution(std::vector<Note*>& notes,Note* note) = 0;

};