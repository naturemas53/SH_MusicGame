#include "EventLane.h"
#include "Lane.h"
#include "../Judgement/JudgementContext.h"
#include "../ArrayAlgorithm/DeleteNoteAlgorithm.h"
#include "../MultiMouseDevice.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"
#include "../Lane/JudgeBomb.h"
#include "../../yoshi/effect/Effect_Singleton.h"
#include <typeinfo>

EventLane::EventLane(JudgementContext* judgement){


	offscreen =  GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	this->postMethod_ = nullptr;

	this->judgement_ = judgement;
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
	this->judgement_->EntryJudgeMethod([this](JUDGE judge){
		this->bomb_->NoticeJudge(judge);
	});

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

void EventLane::Update(DWORD nowTime){

	this->bomb_->Update();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	RawInputMouse& mouse = MultiMouse.GetInputData(0);
	this->judgement_->judgeNote((*itr),nowTime,mouse);

}

void EventLane::Draw(DWORD nowTime){



	SpriteBatch.Begin();

	if (this->postMethod_ != nullptr) this->postMethod_(this->drawJudgeVisitor_);
	SpriteBatch.End();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color(0,0,0,0));
	SpriteBatch.Begin();
	NoteDrawComponent.Draw((*itr),this,nowTime);
	SpriteBatch.End();

	GraphicsDevice.SetDefaultRenderTarget();
	SpriteBatch.Begin();

	SpriteBatch.InitTransform();

	SpriteBatch.DrawSimple(*offscreen, Vector3_Zero);

	SpriteBatch.End();

	std::vector<Effect_Singleton::SHADER_NAME> comands_;
	comands_.push_back(Effect_Singleton::blur);
	comands_.push_back(Effect_Singleton::bloom);

	RENDERTARGET onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comands_,offscreen);
	


	GraphicsDevice.SetDefaultRenderTarget();
	SpriteBatch.Begin();

	SpriteBatch.InitTransform();

	//ブルームアルファ
	SpriteBatch.DrawSimple(*onShaderScreen, Vector3_Zero,0.4f);

	SpriteBatch.End();

}

void EventLane::Accept(VISITORMETHOD visit){visit(this);}

void EventLane::EntryPostMethod(std::function<void(VISITORMETHOD)> postMethod){this->postMethod_ = postMethod;}