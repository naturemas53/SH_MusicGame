/**
* @file SingleNoteJudgement.cpp
* @brief 単押しノート判定クラス 実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "SingleNoteJudgement.h"
#include "../Note/Note/SingleNote.h"
#include <math.h>

SingleNoteJudgement::SingleNoteJudgement(){

}

SingleNoteJudgement::~SingleNoteJudgement(){


}

/**
* @brief 単押しノート判定関数
* @param (judgeNote) 判定するノート
* @param (nowTime) 曲の現在時間
* @param (mouse) 判定マウス
* @return JUDGE　押されたタイミングによってenum JUDGEを返す
* @detail 押されたタイミングによってenum JUDGEを
*		  返す関数です。
*		　押されたときにenum JUDGE::MISS以上であれば
*		  押したタイミングに応じたenum JUDGEを返し、
*		  そうでなければenum JUDGE::NONEを返します。
*/
JUDGE SingleNoteJudgement::Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse){

	//そもそも単押しノートかどうかチェック
	if (judgeNote->GetType() != Note::SINGLENOTE) return MISS;

	//現在の時間と判定するノートのタイミングの差を取る
	long dirTime = nowTime - judgeNote->GetTiming();
	//放置しすぎのミス
	if (dirTime > (long)JUDGE::MISS) return MISS;

	if (mouse.IsPushed(LEFTBUTTON) || mouse.IsPushed(RIGHTBUTTON)){
		return Judgement::judgeResponsib_->Judge(labs(nowTime - judgeNote->GetTiming()));
	}

	return NONE;

}