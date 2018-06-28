#pragma once
#include "../../../ESGLib.h"
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
	void EntryComboUpMethod(ISRUN teams,NOTICE notice);
	void EntryComboBreakMethod(NOTICE notice);

private:

	int combo_;

	std::vector<std::pair<ISRUN,NOTICE> > comboUpMethods_;
	std::vector<NOTICE> comboBreakMethods_;

	//‚Å‚Î‚Î‚Î
	FONT font_;
	SPRITE combo_image;
	RENDERTARGET offscreen[2];

};