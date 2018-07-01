#pragma once
#include <d3dx9.h>
#include <vector>
#include "../Judgement/JudgeCounter.h"

enum JUDGE;
class Combo;
class Score;
class BackMovie;

class UI{

public:

	UI();
	~UI();

	void Update(DWORD nowTime);
	void Draw(DWORD nowTime);

	void NoticeJudge(JUDGE value);
	void NoticeNoteCount(int noteCount);

	void GetScoreAndJudgeCount(int& score,JudgeCounter& counter);

private:

	Score* score_;
	Combo* combo_;
	BackMovie* movie_;

};