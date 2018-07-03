#pragma once
#include "TitleDisplayScene.h"
#include "../FadeInOut.h"

class ImageDisplayScene : public TitleDisplayScene{

public:

	ImageDisplayScene(){}
	~ImageDisplayScene(){}

	static ImageDisplayScene& GetInstance(){

		static ImageDisplayScene instance;
		return instance;

	}

	virtual void LoadResource();
	virtual void ReleaseResource();
	virtual void Initialize();
	virtual void Finalize();
	virtual TitleDisplayScene* Update();
	virtual void Draw();

private:

	void AlphaChange();

	enum ALPHA_STATE{

		UP,
		DOWN

	}alpha_state_;

	float stringAlpha_;

	SPRITE clickStrSp_;
	SPRITE titleSp_;
	FadeInOut fade_;
	int time_;

};