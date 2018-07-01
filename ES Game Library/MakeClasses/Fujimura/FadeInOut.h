#pragma once
#include "../../ESGLib.h"

class FadeInOut{

public:

	enum FADETYPE{

		FADE_IN,
		FADE_OUT

	};

	FadeInOut();
	~FadeInOut();

	bool Update();
	void Draw();

	void ChangeFade(FADETYPE nextFade,int fadeTime);

private:

	FADETYPE fadetype_;
	float alpha_;
	int elapsedTime_;
	int fadeTime_;

	RENDERTARGET offScreen_;

};