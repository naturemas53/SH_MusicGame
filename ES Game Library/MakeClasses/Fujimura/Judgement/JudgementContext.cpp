#include "JudgementContext.h"
#include "../Note/Note/Note.h"
#include "SingleNoteJudgement.h"
#include "LongNoteJudgement.h"
#include "EventNoteJudgement.h"

JudgementContext::JudgementContext(){

	this->judgements_[Note::SINGLENOTE] = new SingleNoteJudgement();
	this->judgements_[Note::LONGNOTE] = new LongNoteJudgement();
	this->judgements_[Note::EVENTNOTE] = new EventNoteJudgement();

}

JudgementContext::~JudgementContext(){
	
	for (auto instance : this->judgements_) delete instance.second;

}

void JudgementContext::judgeNote(Note* note, DWORD nowTime, RawInputMouse& mouse){

	Note::NOTETYPE type = note->GetType();
	JUDGE judge = this->judgements_[type]->Judge(note,nowTime,mouse);
	if (judge == NONE) return;

	for (auto notice : this->judgeNoticeMethods_) notice(judge);

}

void JudgementContext::EntryJudgeMethod(JUDGENOTICE notice){
	this->judgeNoticeMethods_.push_back(notice);
}