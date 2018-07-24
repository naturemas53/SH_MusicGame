/**
* @file SingleNoteJudgement.cpp
* @brief 単押しノート判定クラス
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