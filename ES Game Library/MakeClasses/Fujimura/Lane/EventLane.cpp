#include "EventLane.h"
#include "../Judgement/JudgementContext.h"
#include "../ArrayAlgorithm/DeleteNoteAlgorithm.h"
#include "../MultiMouseDevice.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"
#include "../Lane/JudgeBomb.h"

EventLane::EventLane(JudgementContext* judgement){

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
	this->bomb_ = new JudgeBomb(Vector3(1280.0f / 2.0f,700.0f,0.0f));
	this->judgement_->EntryJudgeMethod([&](JUDGE judge){

		bomb_->NoticeJudge(judge);

	});

}

EventLane::~EventLane(){

	delete this->bomb_;
}

void EventLane::Update(DWORD nowTime){

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	RawInputMouse& mouse = MultiMouse.GetInputData(0);
	this->judgement_->judgeNote((*itr),nowTime,mouse);

}

void EventLane::Draw(DWORD nowTime){

	this->bomb_->Draw();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	NoteDrawComponent.Draw((*itr),this,nowTime);

}

void EventLane::Accept(VISITORMETHOD visit){

	visit(this);

}