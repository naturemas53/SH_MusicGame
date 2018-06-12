#pragma once
#include "../Judgement/JudgeEnum.h"
#include <functional>
#include <vector>

typedef std::function<bool(int combo)> ISRUN;
typedef std::function<void ()> NOTICE;

class Combo{

public:

	Combo();
	~Combo();

	void Update();
	void Draw();

	void ChangeCombo(JUDGE judge);
	void EntryRankUpMethod(ISRUN teams,NOTICE notice);
	void EntryComboBreakMethod(NOTICE notice);

private:

	int combo_;

	std::vector<std::pair<ISRUN,NOTICE> > rankUpMethods_;
	std::vector<NOTICE> comboBreakMethods_;

};