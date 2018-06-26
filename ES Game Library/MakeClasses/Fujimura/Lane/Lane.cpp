#include "Lane.h"
#include "../DataSingleton.h"
#include "../Judgement/JudgementContext.h"
#include "JudgeBomb.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"

Lane::Lane(Vector3 inPos, JudgementContext* inJudge, int mouseNum) :
SIZE_(Vector2(0.0f,0.0f)),
POS_(inPos){

	this->judge_ = inJudge;
	this->judge_->EntryJudgeMethod([this](JUDGE judge){ 
	
		auto itr = this->notes_.begin();
		if (itr == this->notes_.end()) return;
		delete (*itr);
		this->notes_.erase(itr);

	});

	Vector3 startPos, hitPos;
	this->GetLaneVectol(startPos,hitPos);
	hitPos.y += this->SIZE_.y / 2.0f;
	this->bomb_ = new JudgeBomb();

	this->judge_->EntryJudgeMethod([&](JUDGE judge){
		bomb_->NoticeJudge(judge);
	});

	this->mouseNum_ = mouseNum;

}

Lane::~Lane(){

	delete this->bomb_;

}

void Lane::Update(DWORD nowTime){

	this->bomb_->Update();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	(*itr)->Update();
	this->judge_->judgeNote((*itr), nowTime,MultiMouse.GetInputData(this->mouseNum_));

}

void Lane::Draw(DWORD nowTime){

	//Rect userect = RectWH(0, 0, 512, 80);
	//SPRITE sp = Data.atlasSp_;

	//SpriteBatch.Draw(*sp, this->POS_,userect);

	this->bomb_->Draw(this->POS_);
	for (auto note : this->notes_){
		if (!(NoteDrawComponent.Draw(note, this, nowTime)) )break;
	}
}

void Lane::Accept(VISITORMETHOD visit){visit(this);}

void Lane::GetLaneVectol(Vector3 &startPos, Vector3 &hitPos){

	startPos = this->POS_;
	startPos.x += this->SIZE_.x / 2.0f;
	startPos.y = 0.0f;

	hitPos = this->POS_;
	hitPos.x += this->SIZE_.x / 2.0f;
	hitPos.y += this->SIZE_.y / 2.0f;

}