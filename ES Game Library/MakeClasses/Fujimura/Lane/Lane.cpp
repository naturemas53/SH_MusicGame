/**
* @file Lane.cpp
* @brief ���[���N���X�@������
* @author So Fujimura
* @date 2018/07/05
*/
#include "Lane.h"
#include "../DataSingleton.h"
#include "../Judgement/JudgementContext.h"
#include "JudgeBomb.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"

/**
* @brief Lane�R���X�g���N�^
* @param (inPos) �m�[�g�̏I�_���W
* @param (inJudge) judgementContext�|�C���^�̓o�^
* @param (mouseNum) ���Ԗڂɓo�^���ꂽ�}�E�X�����邩
* @return void
* @detail Lane�R���X�g���N�^�̏������֐��ɂȂ�܂��B
*/
Lane::Lane(Vector3 inPos, JudgementContext* inJudge, int mouseNum) :
SIZE_(Vector2(0.0f,0.0f)),
POS_(inPos){

	this->judge_ = inJudge;

	//���肪���܂�����A���肵���m�[�g������
	this->judge_->EntryJudgeMethod([this](JUDGE judge){ 
	
		auto itr = this->notes_.begin();
		if (itr == this->notes_.end()) return;

		delete (*itr);
		this->notes_.erase(itr);

	});


	this->bomb_ = new JudgeBomb();

	//����ɉ������{�����o��
	this->judge_->EntryJudgeMethod([&](JUDGE judge){
		bomb_->NoticeJudge(judge);
	});

	this->mouseNum_ = mouseNum;

}

Lane::~Lane(){

	delete this->bomb_;

}

/**
* @brief Lane�X�V�֐�
* @param (nowTime) �Ȃ̌��ݎ���
* @return void
* @detail �z��̐擪�̃m�[�g��JudgementContext�ɔ��肵�Ă��炢�܂��B
*/
void Lane::Update(LONG nowTime){

	this->bomb_->Update();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	(*itr)->Update();
	this->judge_->judgeNote((*itr), nowTime,MultiMouse.GetInputData(this->mouseNum_));

}

/**
* @brief Lane�`��֐�
* @param (nowTime) �Ȃ̌��ݎ���
* @return void
* @detail Lane�ɓ����Ă���m�[�g���Ȃ̎��Ԃɍ��킹�A�`�悵�܂��B
*/
void Lane::Draw(LONG nowTime){

	this->bomb_->Draw(this->POS_);

	for (auto note : this->notes_){
		//��ʓ��Ɉڂ�m�[�g�����`�悵�����̂ŁA
		//false���Ԃ��Ă�����`�揈�����I��
		if (!(NoteDrawComponent.Draw(note, this, nowTime)) )break;
	}
}

/**
* @brief �K��֐����󂯓��ꂷ��֐�
* @param (visit) �K�₷��֐�
* @return void
* @detail Visitor�֐����󂯓���܂��B
*/
void Lane::Accept(VISITORMETHOD visit){visit(this);}

/**
* @brief ���[���̎n�_�I�_���擾����֐�
* @param (startPos) ���[���̎n�_���󂯎��ϐ�
* @param (endPos) ���[���̏I�_���󂯎��ϐ�
* @return void (�������A�����Ƃ��ēn�����ϐ��Ƀ��[���̎n�_�ƏI�_������)
* @detail ���[���̎n�_�ƏI�_���擾���܂��B
*		  �������A2�����Ɏ擾����̂�
*		  �߂�l�ł͂Ȃ��A�����ɓn�����ϐ��ɓ���܂��B
*/
void Lane::GetLaneVectol(Vector3 &startPos, Vector3 &hitPos){

	startPos = this->POS_;
	startPos.x += this->SIZE_.x / 2.0f;
	//�ォ��~���Ă���̂�0
	startPos.y = 0.0f;

	hitPos = this->POS_;
	hitPos.x += this->SIZE_.x / 2.0f;
	hitPos.y += this->SIZE_.y / 2.0f;

}