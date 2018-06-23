#pragma once
#include "../Judgement/JudgeEnum.h"

class EventBomb{

public:

	EventBomb();
	~EventBomb();

	void Update();
	void Draw();

	void NoticeJudge(JUDGE judge);

private:

	const int DRAW_TIME_REMAIN_MAX_;
	int drawTimeRemain_;

};