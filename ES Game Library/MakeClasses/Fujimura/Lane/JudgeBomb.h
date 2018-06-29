#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeEnum.h"
#include <string>

class JudgeBomb{

public:

	JudgeBomb();
	~JudgeBomb();

	void Update();
	void Draw(Vector3 pos);
	void NoticeJudge(JUDGE judge);

private:

	const int MAX_PAL_VALUE_;

	int palValue_;
	Rect useRect_;

};