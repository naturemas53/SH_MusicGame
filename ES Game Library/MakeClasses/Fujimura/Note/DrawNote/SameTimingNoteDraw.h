/**
* @file SameTimingNoteDraw.h
* @brief 同じタイミングのノートの特殊エフェクトを描画するクラス
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