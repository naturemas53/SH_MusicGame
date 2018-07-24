#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"
#include "../MakeClasses/Fujimura/Judgement/JudgeCounter.h"
#include "../MakeClasses/Fujimura/FadeInOut.h"
#include "../MakeClasses/Fujimura/ResultScene/IntValueSimpleDraw.h"

class ResultScene : public CGameScene {
public:
	ResultScene()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~ResultScene()
	{
		Finalize();

#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		/*GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();*/
	}

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();

private:
	// 変数宣言
	SPRITE  result_image;
	SPRITE judgeSp_;
	SPRITE numberSp_;
	SPRITE growSp_;
	SPRITE scoreSp_;

	SPRITE thankStrSp_;
	SPRITE thankGrowSp_;

	JudgeCounter counter_;
	int score_;
	IntValueSimpleDraw* drawJudgeValue_;
	IntValueSimpleDraw* drawScoreValue_;

	int elapsedTime_;

	//透明不透明
	FadeInOut fade_;

	enum ALPHA_STATE{

		UP,
		DOWN

	}alpha_state_;

	float stringAlpha_;


	// 関数プロトタイプ
	void AlphaChange();


};
