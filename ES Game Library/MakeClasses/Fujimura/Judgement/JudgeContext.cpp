#include "JudgeContext.h"
#include "../Note/Note/Note.h"
#include "SingleNoteJudgement.h"

JudgeContext::JudgeContext(){

	this->judgements_[Note::SINGLENOTE] = new SingleNoteJudgement();
	//this->judgements_[Note::LONGNOTE] = SingleNoteJudgement();
	//this->judgements_[Note::EVENTNOTE] = SingleNoteJudgement();

}

JudgeContext::~JudgeContext(){
	
	for (auto instance : this->judgements_) delete instance.second;

}

void JudgeContext::judgeNote(Note* note,DWORD nowTime,RawInputMouse& mouse){

	Note::NOTETYPE type = note->GetType();
	JUDGE judge = this->judgements_[type]->Judge(note,nowTime,mouse);
	if (judge == NONE) return;

	for (auto notice : this->judgeNoticeMethods_) notice(judge);

}

void JudgeContext::EntryJudgeMethod(JUDGENOTICE notice){
	this->judgeNoticeMethods_.push_back(notice);
}