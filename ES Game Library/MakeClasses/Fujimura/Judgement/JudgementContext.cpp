/**
* @file JudgementContext.cpp
* @brief JudgementContext�N���X�@������
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
* @brief ����֐�
* @param (judgeNote) ���肷��m�[�g
* @param (nowTime) �Ȃ̌��ݎ���
* @param (mouse) ����}�E�X
* @return void (����̓N���X���ɓo�^���ꂽ�֐����Ăяo�����Ƃōs��)
* @sa JudgementContext::EntryJudgeMethod()
* @detail �l�X�ȃm�[�g�ɍ��킹�Ĕ��菈����؂�ւ��A
*		  ���茋�ʂ��A�֐����ĂԌ`�Œʒm����N���X�ɂȂ�܂��B
*/
void JudgementContext::judgeNote(Note* note, LONG nowTime, RawInputMouse& mouse){

	//���肷��m�[�g����m�[�g�̎�ނ�ǂݎ��A
	//���̎�ނɍ��킹�Ĕ��菈����ς��Ă���
	Note::NOTETYPE type = note->GetType();
	JUDGE judge = this->judgements_[type]->Judge(note,nowTime,mouse);

	if (judge == NONE) return;

	//���肪�o����A�o�^���ꂽ�֐��ɒʒm
	for (auto notice : this->judgeNoticeMethods_) notice(judge);

}

/**
* @brief �����ʒm����֐���o�^
* @param (notice) �ʒm�֐�
* @return void
* @detail ���肪�o���ۂɎ󂯎�肽���֐���o�^����֐��ɂȂ�܂��B
*/
void JudgementContext::EntryJudgeMethod(JUDGENOTICE notice){
	this->judgeNoticeMethods_.push_back(notice);
}