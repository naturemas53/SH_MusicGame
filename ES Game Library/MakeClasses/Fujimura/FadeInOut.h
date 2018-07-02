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

	void ReleaseRenderTarget();

	void ChangeFade(FADETYPE nextFade,int fadeTime);
	FADETYPE GetType(){ return this->fadetype_; }

private:

	FADETYPE fadetype_;
	float alpha_;
	int elapsedTime_;
	int fadeTime_;

	RENDERTARGET offScreen_;

};