#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeEnum.h"
#include <string>
#include <map>

class NoteBomb;

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
	Vector3 rivisionPos_;
	std::map<JUDGE,NoteBomb*> noteBombs_;
	NoteBomb* nowBomb_;

};