/**
* @file SingleNoteJudgement.cpp
* @brief �P�����m�[�g����N���X
* @author So Fujimura
* @date 2018/07/05
*/
#pragma once
#include "Judgement.h"

class SingleNoteJudgement : public Judgement{

public:
	SingleNoteJudgement();
	virtual ~SingleNoteJudgement();

	virtual JUDGE Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse);


};