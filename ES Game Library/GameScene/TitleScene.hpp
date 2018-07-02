#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"
#include "../MakeClasses/Fujimura/FadeInOut.h"
#include "../MakeClasses/Fujimura/TitleScene/TitleDisplayContext.h"

class TitleScene : public CGameScene {
public:
	TitleScene()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~TitleScene()
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
		//MediaManager.ReleaseAllMedia();

		//SoundDevice.ReleaseAllMusics();
		//SoundDevice.ReleaseAllSounds();

		//GraphicsDevice.ReleaseAllRenderTargets();
		//GraphicsDevice.ReleaseAllStateBlocks();
		//GraphicsDevice.ReleaseAllFonts();
		//GraphicsDevice.ReleaseAllSprites();
		//GraphicsDevice.ReleaseAllAnimationModels();
		//GraphicsDevice.ReleaseAllModels();
		//GraphicsDevice.ReleaseAllVertexBuffers();
		//GraphicsDevice.ReleaseAllEffects();
	}

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();

private:
	// 変数宣言

	enum ALPHA_STATE{

		UP,
		DOWN

	}alpha_state_;

	SPRITE stringSp_;
	float stringAlpha_;

	TitleDisplayContext context_;
	FadeInOut fade_;

	// 関数プロトタイプ
	//透明不透明
	void AlphaChange();

};