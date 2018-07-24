/**
* @file DetectMultiMotion.cpp
* @brief  �}�E�X�̈�A�̓��������m����N���X ������
* @author So Fujimura
* @date 2018/07/05
*/
#include "DetectMultiMotion.h"

DetectMultiMotion::DetectMultiMotion(){

	this->mouseDetection_ = MouseMotionDetection();

}

DetectMultiMotion::~DetectMultiMotion(){


}

void DetectMultiMotion::Initialize(){

	//���݌��Ă锻��̈ʒu���͂��߂�
	this->nowNorm_ = this->normMoves_.begin();
	if (this->nowNorm_ == this->normMoves_.end()) return;
	MOVESET set = (*this->nowNorm_);
	this->mouseDetection_.SetState(set.first,set.second);

}

/**
* @brief �}�E�X�̈�A�̓��������m����֐�
* @param (mouse) �������炤�}�E�X
* @return bool ��A�̓����S�Ă��I�������ǂ���
* @detail �����̓��������Ԃɔ��肵�Ă����A
*		  �S�Ă̓������I��������true�A
*		  ����ȊO��false��Ԃ��܂��B
*/
bool DetectMultiMotion::Update(RawInputMouse& mouse){

	bool completedFlag = this->mouseDetection_.Update(mouse);
	if (!completedFlag) return false;
	
	auto e_itr = this->normMoves_.end();
	e_itr--;

	//�Ō�̓����łȂ����
	if (this->nowNorm_ != e_itr){
		//���̓������Z�b�g����
		this->nowNorm_++;
		MOVESET set = (*this->nowNorm_);
		this->mouseDetection_.SetState(set.first, set.second);
		return false;
	}

	//�����܂ŗ����Ƃ��͂��ׂďI��点��
	return true;

}

void DetectMultiMotion::AddNormSet(MOVESET addSet){

	this->normMoves_.push_back(addSet);

}