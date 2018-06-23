#pragma once
#include "JudgeEnum.h"
#include "Judgement.h"
#include "../Note/Note/Note.h"
#include "../RawInputMouse.h"
#include <vector>
#include <map>
#include <functional>

typedef std::function<void(JUDGE judge)> JUDGENOTICE;

class JudgementContext{

public:

	JudgementContext();
	~JudgementContext();

	void judgeNote(Note* note, DWORD nowtime, RawInputMouse& mouse);

	void EntryJudgeMethod(JUDGENOTICE judgenotice);

private:

	std::map<Note::NOTETYPE,Judgement* > judgements_;
	std::vector<JUDGENOTICE> judgeNoticeMethods_;

};