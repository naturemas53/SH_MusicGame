#include "AddNoteAlgorithm.h"
#include "../Note/Note/Note.h"

/**
* @file AddNoteAlgorithm.cpp
* @brief �m�[�g�z��\�[�g�A�v�f�ǉ��N���X�@������
* @author So Fujimura
* @date 2018/07/05
*/

/**
* @brief Note�C���X�^���X�v�f�ǉ��֐�
* @param (insertnote) �V�����ǉ�����m�[�g
* @param (notes) �������Ă�m�[�g�̏W�܂�
* @return void
* @detail 1�P�̗v�f�����Ă����āA
*		  �K�؂ȏꏊ�ɑ}������֐��ł��B
*/
void AddNoteAlgorithm::Execution(std::vector<Note*>& notes, Note* insertnote){
	
	// ��������1�������ĂȂ��Ȃ��r�������ɒǉ�
	if (notes.size() == 0){
		notes.push_back(insertnote);
		return;
	}

	int targetTiming = insertnote->GetTiming();
	auto itr = notes.begin();

	while (itr != notes.end()){

		// �P�P�̗v�f�Ɣ�r���A
		// �����Ă�v�f�̃^�C�~���O��
		// �}�����悤�Ƃ��Ă�^�C�~���O���x�����
		// ���̗v�f�̎�O�ɑ}��
		if (targetTiming < (*itr)->GetTiming()){
			notes.insert(itr, insertnote);
			return;
		}

		itr++;

	}

	//�����܂ŗ����ꍇ�͂ǂ̗v�f�����x������
	notes.push_back(insertnote);

}