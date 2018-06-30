#include "UI.h"
#include "../Judgement/JudgeCounter.h"
#include "Combo.h"
#include "Score.h"
#include "BackMovie.h"

UI::UI(){

	this->combo_ = new Combo();
	this->movie_ = new BackMovie();

	ISRUN teams = [](int combo){ return combo % 5 == 0; };
	NOTICE notice = [&](){ movie_->MovieChange(); };
	this->combo_->EntryComboUpMethod(teams,notice);

	notice = [&](){ movie_->MovieReset(); };
	this->combo_->EntryComboBreakMethod(notice);

	this->score_ = new Score(0.5f);

}

UI::~UI(){

	delete this->movie_;
	delete this->combo_;
	delete this->score_;

}

void UI::Update(DWORD nowTime){

	this->movie_->Update();
}

void UI::Draw(DWORD nowTime){


	this->movie_->Draw();

	this->combo_->Draw();

	this->score_->Draw();


}

void UI::NoticeJudge(JUDGE judge){

	this->combo_->ChangeCombo(judge);
	this->score_->NoticeJudge(judge);

}

void UI::NoticeNoteCount(int noteCount){ this->score_->SetNoteCount(noteCount); }