#include "UI.h"
#include "../Judgement/JudgeCounter.h"
#include "Combo.h"
#include "BackMovie.h"

UI::UI(){

	this->combo_ = new Combo();
	this->movie_ = new BackMovie();

	ISRUN teams = [](int combo){ return combo % 5 == 0; };
	NOTICE notice = [&](){ movie_->MovieChange(); };
	this->combo_->EntryComboUpMethod(teams,notice);

	notice = [&](){ movie_->MovieReset(); };
	this->combo_->EntryComboBreakMethod(notice);

}

UI::~UI(){

	delete this->movie_;
	delete this->combo_;

}

void UI::Update(DWORD nowTime){

	this->movie_->Update();
}

void UI::Draw(DWORD nowTime){

	this->movie_->Draw();
	this->combo_->Draw();

}

void UI::NoticeJudge(JUDGE judge){

	this->combo_->ChangeCombo(judge);

}