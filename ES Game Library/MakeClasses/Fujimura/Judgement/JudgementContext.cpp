/**
* @file JudgementContext.cpp
* @brief JudgementContextクラス　実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "JudgementContext.h"
#include "../Note/Note/Note.h"
#include "SingleNoteJudgement.h"
#include "LongNoteJudgement.h"
#include "EventNoteJudgement.h"

JudgementContext::JudgementContext(){

	this->judgements_[Note::SINGLENOTE] = new SingleNoteJudgement();
	this->judgements_[Note::LONGNOTE] = new LongNoteJudgement();
	this->judgements_[Note::EVENTNOTE] = new EventNoteJudgement();

}

JudgementContext::~JudgementContext(){
	
	for (auto instance : this->judgements_) delete instance.second;

}

/**
* @brief 判定関数
* @param (judgeNote) 判定するノート
* @param (nowTime) 曲の現在時間
* @param (mouse) 判定マウス
* @return void (判定はクラス内に登録された関数を呼び出すことで行う)
* @sa JudgementContext::EntryJudgeMethod()
* @detail 様々なノートに合わせて判定処理を切り替え、
*		  判定結果を、関数を呼ぶ形で通知するクラスになります。
*/
void JudgementContext::judgeNote(Note* note, LONG nowTime, RawInputMouse& mouse){

	//判定するノートからノートの種類を読み取り、
	//その種類に合わせて判定処理を変えている
	Note::NOTETYPE type = note->GetType();
	JUDGE judge = this->judgements_[type]->Judge(note,nowTime,mouse);

	if (judge == NONE) return;

	//判定が出たら、登録された関数に通知
	for (auto notice : this->judgeNoticeMethods_) notice(judge);

}

/**
* @brief 判定を通知する関数を登録
* @param (notice) 通知関数
* @return void
* @detail 判定が出た際に受け取りたい関数を登録する関数になります。
*/
void JudgementContext::EntryJudgeMethod(JUDGENOTICE notice){
	this->judgeNoticeMethods_.push_back(notice);
}