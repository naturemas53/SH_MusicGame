#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeEnum.h"
#include <vector>
#include <functional>

class Lane;
class MusicScoreIO;
class UI;

typedef std::function<void(JUDGE judge)> JUDGENOTICE;

class LaneManager{

public:

	LaneManager(MusicScoreIO* io);
	~LaneManager();

	void Update(DWORD nowtime);
	void Draw(DWORD nowtime);

	void EntryJudgeMethod(JUDGENOTICE);

private:

	std::vector<Lane*> lanes_;
	UI* ui_;

	std::vector<JUDGENOTICE> judgeNoticeMethods_;
	//審判系のやつ配列３つ　ストラテジ　judgment

};