#pragma once
/**
* @file ArrayAlgorithm.h
* @brief ノート配列ソート関連インターフェイス
* @author So Fujimura
* @date 2018/07/05
*/
#include <vector>

class Note;

class ArrayAlgorithm{

public:

	ArrayAlgorithm(){};
	~ArrayAlgorithm(){};

	virtual void Execution(std::vector<Note*>& notes,Note* note) = 0;

};