/**
* @file EventNoteJudgement.cpp
* @brief �C�x���g�m�[�g����N���X ������
* @author So Fujimura
* @date 2018/07/05
*/
#include "EventNoteJudgement.h"
#include "../Note/Note/EventNote.h"
#include "../MultiMouseDevice.h"

EventNoteJudgement::EventNoteJudgement(){

	//�}�E�X2���̃C���X�^���X��z��ɑ��
	this->mouseDetections_.push_back(DetectMultiMotion());
	this->mouseDetections_.push_back(DetectMultiMotion());

	//�����ƈړ��ʂ̃y�A
	DetectMultiMotion::MOVESET set;
	set.first = MouseMotionDetection::MOVE_UP;
	set.second = 30;
	//�y�A���Z�b�g
	this->mouseDetections_[0].AddNormSet(set);
	this->mouseDetections_[1].AddNormSet(set);

	set.first = MouseMotionDetection::MOVE_RIGHT;
	set.second = 10;
	this->mouseDetections_[0].AddNormSet(set);

	set.first = MouseMotionDetection::MOVE_LEFT;
	set.second = 10;
	this->mouseDetections_[1].AddNormSet(set);

	//�n�[�g����̐i�s�󋵏�����
	this->DetectionInitialize();

	//!���b�ȓ��ɏ����Ă�
	this->remainMoveLimit_ = 2000;

}

EventNoteJudgement::~EventNoteJudgement(){



}

/**
* @brief �C�x���g�m�[�g����֐�
* @param (judgeNote) ���肷��m�[�g
* @param (nowTime) �Ȃ̌��ݎ���
* @param (mouse) ����}�E�X
* @return JUDGE�@�����ꂽ�^�C�~���O�ɂ����enum JUDGE��Ԃ�
* @detail �n�[�g�����������ǂ�����enum JUDGE�̒l��Ԃ�
*		  �֐��ł��B
*		  �������ԓ��Ƀn�[�g��`�����enum JUDGE::PERFECT��
*		  �������Ԃ𒴂����enum JUDGE::MISS��
*		  ����ȊO��enum JUDGE::NONE��Ԃ��܂��B
*/
JUDGE EventNoteJudgement::Judge(Note* note, LONG nowTime, RawInputMouse& mouse){

	if (note->GetType() != Note::EVENTNOTE) return MISS;

	long dirTime = note->GetTiming() - nowTime;
	if (this->remainMoveLimit_ < dirTime) return JUDGE::NONE;
	if (dirTime < -MISS){
		//NONE�ȊO�̔�����o���ۂ̓n�[�g����̐i�s�x��������
		this->DetectionInitialize();
		return MISS;
	}

	if (this->MoveCheck(0) && this->MoveCheck(1) ){

		//NONE�ȊO�̔�����o���ۂ̓n�[�g����̐i�s�x��������
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