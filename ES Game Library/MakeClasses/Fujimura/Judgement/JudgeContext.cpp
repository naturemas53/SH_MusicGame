#include "JudgeContext.h"
#include "../Note/Note/Note.h"
#include "SingleNoteJudgement.h"

JudgeContext::JudgeContext(){

	this->judgements_[Note::SINGLENOTE] = new SingleNoteJudgement();
	//this->judgements_[Note::LONGNOTE] = new SingleNoteJudgement();
	//this->judgements_[Note::EVENTNOTE] = new SingleNoteJudgement();

}

JudgeContext::~JudgeContext(){
	
}

void JudgeContext::judgeNote(Note* note){

	Note::NOTETYPE type = note->GetType();
	JUDGE judge = this->judgements_[type]->Judge(note);
	if (judge == NONE) return;

	for (auto notice : this->EntryJudgeMethod) notice(judge);

}

void JudgeContext::EntryJudgeMethod(JUDGENOTICE notice){
	this->judgeNoticeMethods_.push_back(notice);
}