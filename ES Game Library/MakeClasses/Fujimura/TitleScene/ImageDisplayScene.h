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

	SPRITE titleSp_;
	FadeInOut fade_;
	int time_;

};