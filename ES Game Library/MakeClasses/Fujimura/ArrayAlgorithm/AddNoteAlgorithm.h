#pragma once
#include "ArrayAlgorithm.h"

/**
* @file AddNoteAlgorithm.h
* @brief ノート配列ソート、要素追加クラス
* @author So Fujimura
* @date 2018/07/05
*/
class AddNoteAlgorithm : public ArrayAlgorithm{

public:

	AddNoteAlgorithm(){};
	~AddNoteAlgorithm(){};

	virtual void Execution(std::vector<Note*>& notes, Note* note);

};