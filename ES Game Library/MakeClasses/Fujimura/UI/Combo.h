#pragma once
#include "../../../ESGLib.h"
#include "../Judgement/JudgeEnum.h"
#include <functional>
#include <vector>

typedef std::function<bool(int combo)> ISRUN;
typedef std::function<void ()> NOTICE;

class Combo{

public:

	Combo(float scale);
	~Combo();

	void Update();
	void Draw();

	void ChangeCombo(JUDGE judge);
	void EntryComboUpMethod(ISRUN teams,NOTICE notice);
	void EntryComboBreakMethod(NOTICE notice);

	void ChengeColor();
	void ColorReset();

private:

	void NumberDraw(SPRITE sp,Vector3 pos,int number);

	const float SCALE_;
	const Vector2 NUMBERSIZE_;
	const Vector2 NUMBER_GROW_SIZE_;
	const Vector2 TEXTSIZE_;
	const Vector2 TEXT_GROW_SIZE_;

	int combo_;
	std::vector<Color> colors_;
	std::vector<Color>::iterator nowColor_;

	std::vector<std::pair<ISRUN,NOTICE> > comboUpMethods_;
	std::vector<NOTICE> comboBreakMethods_;

	SPRITE numberSp_;
	SPRITE numberGrowSp_;
	SPRITE textSp_;
	SPRITE textGrowSp_;
	RENDERTARGET offscreen_;

};