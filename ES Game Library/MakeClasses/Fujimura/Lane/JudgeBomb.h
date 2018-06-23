#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeEnum.h"
#include <string>

class JudgeBomb{

public:

	JudgeBomb(Vector3 drawPos);
	~JudgeBomb();

	void Update();
	void Draw();
	void NoticeJudge(JUDGE judge);

private:

	const int MAX_PAL_VALUE_;

	Vector3 drawPos_;
	int palValue_;

	//Rect useRect_;

	//test
	FONT font_;
	std::wstring judgeStr_;
	Color color_;

};