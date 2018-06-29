#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeCounter.h"

class Score{

public:

	Score(Vector3 drawPos, int noteCount_,float scale);
	~Score();

	void Update();
	void Draw();

	void NoticeJudge(JUDGE judge);

	int GetScore(){ return this->score_; }
	JudgeCounter GetJudgeCount(){ return this->counter_; }

private:

	void NumberDraw(Vector3 pos, int number);

	const Vector3 POS_;
	const Vector2 NUMBERSIZE_;
	int noteCount_;
	JudgeCounter counter_;

	int score_;

	SPRITE textSp_;
	SPRITE numberSp_;
	RENDERTARGET offScreen_;

};