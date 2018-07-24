/**
* @file LongNoteJudgement.cpp
* @brief 長押しノート判定クラス 実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "LongNoteJudgement.h"
#include "SingleNoteJudgement.h"
#include "../Note/Note/LongNote.h"
#include "../DataSingleton.h"
#include "../ClapSingleton.h"

LongNoteJudgement::LongNoteJudgement() :
OK_RELEASE_TIME_(Data.LONG_OK_RELEASE_TIME_)
{
	
	this->releaseTime_ = 0;

}

LongNoteJudgement::~LongNoteJudgement(){



}

/**
* @brief 長押しノート判定関数
* @param (judgeNote) 判定するノート
* @param (nowTime) 曲の現在時間
* @param (mouse) 判定マウス
* @return JUDGE　ホイールを回すタイミングによってenum JUDGEを返す
* @detail ホイールを回している状況によって、
*		  enum JUDGEを返す関数です。
*		  ホイールを回しつづければenum JUDGEの判定が返ります。
*		  ホイールを一定時間回さなかったり、そもそも回し始めないと
*		  enum JUDGE::MISSが返ります。
*		  それ以外はenum JUDGE::NONEが返ります。
*/
JUDGE LongNoteJudgement::Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse){

	//そもそも長押しノートかどうかチェック
	if (judgeNote->GetType() != Note::LONGNOTE)  return MISS;

	//LongNoteの関数を使用するのでキャスト
	//LongNoteであることは上記のチェックで確認済み
	LongNote* longNote = (LongNote*)judgeNote;
	int wheelValue = mouse.GetWheelValue();

	if (!longNote->IsPushed()){
		long dirTime = (long)nowTime - (long)longNote->GetTiming();
		if (dirTime > (long)JUDGE::MISS) return MISS;

		JUDGE result = NONE;
		if (wheelValue != 0){ result = this->judgeResponsib_->Judge(labs(dirTime)); }
		if (result == MISS) return MISS;
		if (result != NONE) {

			//ミスせずに回し始めたら、
			//離した時間の初期化&サウンドを鳴らす
			ClapManager.PlayClap(result);
			longNote->Push();
			this->releaseTime_ = 0;

		}

		//回し始めてないならここで終了
		return NONE;
	}

	this->releaseTime_++;
	if (wheelValue != 0){ this->releaseTime_ = 0; }
	//離している時間が許容時間を超えるとアウト
	if (this->releaseTime_ >= this->OK_RELEASE_TIME_) return MISS;

	//最後まで回しきれたらOK
	if (longNote->GetEndTiming() <= nowTime) return PERFECT;

	return NONE;

}