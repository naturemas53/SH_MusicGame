#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeCounter.h"

class Score{

public:

	Score(Vector3 drawPos,int noteCount_);
	~Score();

	void Update();
	void Draw();

	void NoticeJudge(JUDGE judge);

private:

	const Vector3 POS_;
	JudgeCounter counter_;
	int noteCount_;
	SPRITE numberSp_;

	RENDERTARGET offScreen_;

};