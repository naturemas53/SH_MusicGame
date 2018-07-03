#pragma once
#include "TitleDisplayScene.h"
#include "../FadeInOut.h"

class MovieDisplayScene : public TitleDisplayScene{

public:

	MovieDisplayScene(){}
	~MovieDisplayScene(){}

	static MovieDisplayScene& GetInstance(){

		static MovieDisplayScene instance;
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

	MEDIA movie_;
	FadeInOut fade_;

};;