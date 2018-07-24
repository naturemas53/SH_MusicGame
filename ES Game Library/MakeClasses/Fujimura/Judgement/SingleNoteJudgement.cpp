/**
* @file SingleNoteJudgement.cpp
* @brief �P�����m�[�g����N���X ������
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
* @brief �P�����m�[�g����֐�
* @param (judgeNote) ���肷��m�[�g
* @param (nowTime) �Ȃ̌��ݎ���
* @param (mouse) ����}�E�X
* @return JUDGE�@�����ꂽ�^�C�~���O�ɂ����enum JUDGE��Ԃ�
* @detail �����ꂽ�^�C�~���O�ɂ����enum JUDGE��
*		  �Ԃ��֐��ł��B
*		�@�����ꂽ�Ƃ���enum JUDGE::MISS�ȏ�ł����
*		  �������^�C�~���O�ɉ�����enum JUDGE��Ԃ��A
*		  �����łȂ����enum JUDGE::NONE��Ԃ��܂��B
*/
JUDGE SingleNoteJudgement::Judge(Note* judgeNote, LONG nowTime, RawInputMouse& mouse){

	//���������P�����m�[�g���ǂ����`�F�b�N
	if (judgeNote->GetType() != Note::SINGLENOTE) return MISS;

	//���݂̎��ԂƔ��肷��m�[�g�̃^�C�~���O�̍������
	long dirTime = nowTime - judgeNote->GetTiming();
	//���u�������̃~�X
	if (dirTime > (long)JUDGE::MISS) return MISS;

	if (mouse.IsPushed(LEFTBUTTON) || mouse.IsPushed(RIGHTBUTTON)){
		return Judgement::judgeResponsib_->Judge(labs(nowTime - judgeNote->GetTiming()));
	}

	return NONE;

}