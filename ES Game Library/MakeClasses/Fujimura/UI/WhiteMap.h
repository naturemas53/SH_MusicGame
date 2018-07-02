#pragma once
#include "../../../ESGLib.h"
#include <vector>

class WhiteMap{

public:

	enum STATE{

		NONE,
		SCALE_UP,
		ALPHA_DOWN

	};

	WhiteMap();
	~WhiteMap();

	void Update();
	void Draw();

	void Start();
	void Reset();

	bool IsChangedState();
	STATE GetState(){ return state_; }

private:

	void ScaleUpUpdate();
	void AlphaDownUpdate();

	STATE state_;
	STATE prevState_;

	const int ALPHA_DOWN_TIME_;

	SPRITE sp_;
	float alpha_;
	float scale_;
	int time_;

	std::vector<std::pair<float, int> > scaleAnimations_;
	std::vector<std::pair<float, int> >::iterator nowPosition_;

};