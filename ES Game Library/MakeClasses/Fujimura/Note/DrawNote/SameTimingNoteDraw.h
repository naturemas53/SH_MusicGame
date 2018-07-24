/**
* @file SameTimingNoteDraw.h
* @brief �����^�C�~���O�̃m�[�g�̓���G�t�F�N�g��`�悷��N���X
* @author So Fujimura
* @date 2018/07/21
*/
#pragma once
#include "DrawNote.h"

class SameTimingNoteDraw : public DrawNote{

public:

	SameTimingNoteDraw();
	~SameTimingNoteDraw();

	virtual void NoteDraw(Note* note, BaseLane* lane, LONG nowTime, LONG drawRangeTime);

};