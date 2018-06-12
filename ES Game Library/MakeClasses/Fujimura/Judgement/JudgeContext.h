#pragma once
#include "JudgeEnum.h"
#include "Judgement.h"
#include "../Note/Note/Note.h"
#include <vector>
#include <map>
#include <functional>

typedef std::function<void(JUDGE judge)> JUDGENOTICE;

class JudgeContext{

public:

	JudgeContext();
	~JudgeContext();

	void judgeNote(Note* note);

	void EntryJudgeMethod(JUDGENOTICE judgenotice);

private:

	std::map<Note::NOTETYPE,Judgement*> judgements_;
	std::vector<JUDGENOTICE> judgeNoticeMethods_;

};