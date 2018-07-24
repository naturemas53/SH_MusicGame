/**
* @file EventLane.cpp
* @brief �C�x���g���[���N���X�@������
* @author So Fujimura
* @date 2018/07/05
*/
#include "EventLane.h"
#include "Lane.h"
#include "../Judgement/JudgementContext.h"
#include "../ArrayAlgorithm/DeleteNoteAlgorithm.h"
#include "../MultiMouseDevice.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"
#include "../Lane/JudgeBomb.h"
#include "../../yoshi/effect/Effect_Singleton.h"
#include <typeinfo>

/**
* @brief EventLane�R���X�g���N�^
* @param (JudgementContext) ����C���X�^���X�̃|�C���^
* @return void
* @detail EventLane�R���X�g���N�^�̏������֐��ɂȂ�܂��B
*/
EventLane::EventLane(JudgementContext* judgement){

	//�V�F�[�_�[�p�̃X�N���[����p��
	offscreen =  GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	this->postMethod_ = nullptr;

	this->judgement_ = judgement;

	//���肪�Ԃ��Ă�����m�[�g������
	JUDGENOTICE notice = [this](JUDGE judge){

		std::vector<Note*>& notes = this->GetNoteList();
		auto itr = notes.begin();
		if (itr == notes.end()) return;

		DeleteNoteAlgorithm deletenote;
		deletenote.Execution(notes,(*itr));
		notes.erase(itr);

	};
	this->judgement_->EntryJudgeMethod(notice);

	this->bomb_ = new JudgeBomb();
	//�{���\��
	this->judgement_->EntryJudgeMethod([this](JUDGE judge){
		this->bomb_->NoticeJudge(judge);
	});

	//PERFERCT�Ȃǂ̔���̕������A�ʏ탌�[���̂����ɏo���̂ŁA
	//�O����e�ʏ탌�[����VISITORMETHOD�𓊂����֐���������āA
	//���̊֐��ɔ����\�����鏈���𓊂��܂�
	this->drawJudgeVisitor_ = [this](BaseLane* baselane){
		if (typeid(*baselane) != typeid(Lane)) return;

		Lane* lane = (Lane*)baselane;

		Vector3 startPos, hitPos;
		lane->GetLaneVectol(startPos, hitPos);
		this->bomb_->Draw(hitPos);

	};

}

EventLane::~EventLane(){

	delete this->bomb_;
}


/**
* @brief EventLane�X�V�֐�
* @param (nowTime) �Ȃ̌��ݎ���
* @return void
* @detail EventLane�ɂ���l�X�ȗv�f���X�V���܂��B
*/
void EventLane::Update(LONG nowTime){

	this->bomb_->Update();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	RawInputMouse& mouse = MultiMouse.GetInputData(0);
	this->judgement_->judgeNote((*itr),nowTime,mouse);

}

/**
* @brief EventLane�`��֐�
* @param (nowTime) �Ȃ̌��ݎ���
* @return void
* @detail EventLane�ɓ����Ă���m�[�g��
*		  �u�V�F�[�_�[�������āv
*		  �`�悵�܂��B
*/
void EventLane::Draw(LONG nowTime){

	//�܂�����̕`����e���[���̉��ɍs���܂��B
	SpriteBatch.Begin();
	if (this->postMethod_ != nullptr) this->postMethod_(this->drawJudgeVisitor_);
	SpriteBatch.End();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	//�p�ӂ����ʃX�N���[���Ƀm�[�g��`�悵�܂��B
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color(0,0,0,0));
	SpriteBatch.Begin();
	bool isDraw = NoteDrawComponent.Draw((*itr),this,nowTime);
	SpriteBatch.End();

	if (!isDraw) return;

	//���Ԃɂ�����V�F�[�_�[��z��ɒǉ�
	std::vector<Effect_Singleton::SHADER_NAME> comands_;

	//�z��ɒǉ��������ԂɁA�V�F�[�_�[��K�p�A
	//�K�p��̉摜���Ԃ��Ă��܂��B
	RENDERTARGET onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comands_,offscreen);

	GraphicsDevice.SetDefaultRenderTarget();
	SpriteBatch.Begin();

	//DrawSimple�ł��ƁA��]�s���g��k���s��A�ړ��s��̏��
	//�c�����܂܂Ȃ̂ŁAInitTransform�ŏ�����
	SpriteBatch.InitTransform();

	SpriteBatch.DrawSimple(*onShaderScreen, Vector3_Zero,1.0f);

	SpriteBatch.End();

}

/**
* @brief VISITORMETHOD�󂯓���֐�
* @param (visit) �K��֐�
* @return void
* @detail EventLane�ŏ���������֐����󂯓���܂��B
*/
void EventLane::Accept(VISITORMETHOD visit){visit(this);}

/**
* @brief EventLane�`��֐�
* @param (nowTime) �Ȃ̌��ݎ���
* @return void
* @detail�@
*/
void EventLane::EntryPostMethod(std::function<void(VISITORMETHOD)> postMethod){this->postMethod_ = postMethod;}