#include "EventLane.h"
#include "Lane.h"
#include "../Judgement/JudgementContext.h"
#include "../ArrayAlgorithm/DeleteNoteAlgorithm.h"
#include "../MultiMouseDevice.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"
#include "../Lane/JudgeBomb.h"
#include <typeinfo>

EventLane::EventLane(JudgementContext* judgement){

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
	this->judgement_->EntryJudgeMethod([&](JUDGE judge){

		bomb_->NoticeJudge(judge);

	});

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

	VISITORMETHOD method = [this](BaseLane* baselane){
		if (typeid(*baselane) != typeid(Lane)) return;

		Lane* lane = (Lane*)baselane;

		Vector3 startPos, hitPos;
		lane->GetLaneVectol(startPos,hitPos);
		this->bomb_->Draw(startPos);

	};

	if (this->postMethod_ != nullptr) this->postMethod_(method);

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	NoteDrawComponent.Draw((*itr),this,nowTime);

}

void EventLane::Accept(VISITORMETHOD visit){visit(this);}

void EventLane::EntryPostMethod(std::function<void(VISITORMETHOD)> postMethod){this->postMethod_ = postMethod;}