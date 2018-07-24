#pragma once
#include "ArrayAlgorithm.h"

/**
* @file AddNoteAlgorithm.h
* @brief �m�[�g�z��\�[�g�A�v�f�ǉ��N���X
* @author So Fujimura
* @date 2018/07/05
*/
class AddNoteAlgorithm : public ArrayAlgorithm{

public:

	AddNoteAlgorithm(){};
	~AddNoteAlgorithm(){};

	virtual void Execution(std::vector<Note*>& notes, Note* note);

};