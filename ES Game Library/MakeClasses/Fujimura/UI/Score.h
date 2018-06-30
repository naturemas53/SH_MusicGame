#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeCounter.h"

class Score{

public:

	Score(float scale);
	~Score();

	void Update();
	void Draw();

	void NoticeJudge(JUDGE judge);

	void SetNoteCount(int noteCount);

	int GetScore(){ return this->score_; }
	JudgeCounter GetJudgeCount(){ return this->counter_; }

private:

	void NumberDraw(Vector3 pos, int number);

	const Vector2 NUMBERSIZE_;
	const float SCALE_;

	int noteCount_;
	JudgeCounter counter_;

	int score_;

	SPRITE textSp_;
	SPRITE numberSp_;
	RENDERTARGET offScreen_;

};