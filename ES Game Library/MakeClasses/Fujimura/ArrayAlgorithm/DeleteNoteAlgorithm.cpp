#include "DeleteNoteAlgorithm.h"
#include "../Note/Note/Note.h"

/**
* @file DeleteNoteAlgorithm.cpp
* @brief �m�[�g�z��\�[�g�A�v�f����N���X�@������
* @author So Fujimura
* @date 2018/07/05
*/

/**
* @brief Note�C���X�^���X�v�f�ǉ��֐�
* @param (insertnote) �V�����ǉ�����m�[�g
* @param (notes) �������Ă�m�[�g�̏W�܂�
* @return void
* @detail �w�肳�ꂽ�v�f��T���A
*		  ����΂��̗v�f�̃C���X�^���X���J������
*         �֐��ł��B
*/
void DeleteNoteAlgorithm::Execution(std::vector<Note*>& notes, Note* note){

	auto itr = std::find(notes.begin(),notes.end(),note);
	if (itr != notes.end()) delete note;

}