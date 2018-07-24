/**
* @file EventNoteJudgement.cpp
* @brief イベントノート判定クラス 実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "EventNoteJudgement.h"
#include "../Note/Note/EventNote.h"
#include "../MultiMouseDevice.h"

EventNoteJudgement::EventNoteJudgement(){

	//マウス2つ分のインスタンスを配列に代入
	this->mouseDetections_.push_back(DetectMultiMotion());
	this->mouseDetections_.push_back(DetectMultiMotion());

	//方向と移動量のペア
	DetectMultiMotion::MOVESET set;
	set.first = MouseMotionDetection::MOVE_UP;
	set.second = 30;
	//ペアをセット
	this->mouseDetections_[0].AddNormSet(set);
	this->mouseDetections_[1].AddNormSet(set);

	set.first = MouseMotionDetection::MOVE_RIGHT;
	set.second = 10;
	this->mouseDetections_[0].AddNormSet(set);

	set.first = MouseMotionDetection::MOVE_LEFT;
	set.second = 10;
	this->mouseDetections_[1].AddNormSet(set);

	//ハート判定の進行状況初期化
	this->DetectionInitialize();

	//!何秒以内に書いてね
	this->remainMoveLimit_ = 2000;

}

EventNoteJudgement::~EventNoteJudgement(){



}

/**
* @brief イベントノート判定関数
* @param (judgeNote) 判定するノート
* @param (nowTime) 曲の現在時間
* @param (mouse) 判定マウス
* @return JUDGE　押されたタイミングによってenum JUDGEを返す
* @detail ハートをかけたかどうかでenum JUDGEの値を返す
*		  関数です。
*		  制限時間内にハートを描ければenum JUDGE::PERFECTを
*		  制限時間を超えるとenum JUDGE::MISSを
*		  それ以外はenum JUDGE::NONEを返します。
*/
JUDGE EventNoteJudgement::Judge(Note* note, LONG nowTime, RawInputMouse& mouse){

	if (note->GetType() != Note::EVENTNOTE) return MISS;

	long dirTime = note->GetTiming() - nowTime;
	if (this->remainMoveLimit_ < dirTime) return JUDGE::NONE;
	if (dirTime < -MISS){
		//NONE以外の判定を出す際はハート判定の進行度を初期化
		this->DetectionInitialize();
		return MISS;
	}

	if (this->MoveCheck(0) && this->MoveCheck(1) ){

		//NONE以外の判定を出す際はハート判定の進行度を初期化
		this->DetectionInitialize();
		return JUDGE::PERFECT;

	}


	return JUDGE::NONE;

}

void EventNoteJudgement::DetectionInitialize(){

	for (int i = 0; i < this->mouseDetections_.size(); i++){

		this->mouseDetections_[i].Initialize();

	}

}

bool EventNoteJudgement::MoveCheck(int mousenum){

	RawInputMouse& mouse = MultiMouse.GetInputData(mousenum);

	return this->mouseDetections_[mousenum].Update(mouse);

}