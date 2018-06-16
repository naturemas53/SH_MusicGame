#include "Lane.h"
#include "../Note/Note/Note.h"
#include "../DataSingleton.h"
#include "../Judgement/JudgeContext.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"

Lane::Lane(Vector3 inPos, JudgeContext* inJudge, int mouseNum) :
SIZE_(Vector2(512.0f,100.0f)),
POS_(inPos){

	this->judge_ = inJudge;
	std::vector<Note*>& notes = this->notes_;
	this->judge_->EntryJudgeMethod([&](JUDGE judge){ 
	
		auto itr = notes.begin();
		if (itr == notes.end()) return;
		delete (*itr);
		notes.erase(itr);

	});

	this->mouseNum_ = mouseNum;

}

Lane::~Lane(){

	for (auto note : this->notes_) delete note;

}

void Lane::Update(DWORD nowTime){

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	this->judge_->judgeNote((*itr), nowTime,MultiMouse.GetInputData(this->mouseNum_));

}

void Lane::Draw(DWORD nowTime){

	//テストコードマーン
	Rect userect = RectWH(0, 0, 512, 80);
	SPRITE sp = Data.atlasSp_;

	SpriteBatch.Draw(*sp, this->POS_,userect);

	for (auto note : this->notes_){
		if (!(NoteDrawComponent.Draw(note, this, nowTime)) )break;
	}
}

void Lane::AddNote(Note* note){

	//そもそも入ってないなら入れて終わり
	if (this->notes_.size() == 0){
		notes_.push_back(note);
		return;
	}

	int insertTiming = note->GetTiming();
	auto itr = this->notes_.begin();

	while (itr != this->notes_.end()){

		if (insertTiming < (*itr)->GetTiming()){

			this->notes_.insert(itr, note);
			return;

		}

		itr++;

	}

	//ここまで来たときは１番遅い
	notes_.push_back(note);

}

void Lane::EraseNote(Note* deletenote){

	auto itr = std::find(this->notes_.begin(), this->notes_.end(),deletenote);
	if (itr == this->notes_.end()) return;

	delete deletenote;
	this->notes_.erase(itr);

}

void Lane::GetLaneVectol(Vector3 &startPos, Vector3 &hitPos){

	startPos = this->POS_;
	startPos.x += this->SIZE_.x / 2.0f;
	startPos.y = 0.0f;

	hitPos = this->POS_;
	hitPos.x += this->SIZE_.x / 2.0f;
	hitPos.y += this->SIZE_.y / 2.0f;

}