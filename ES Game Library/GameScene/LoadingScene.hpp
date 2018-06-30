#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"
#include <future>

class LoadingScene : public CGameScene {
public:
	LoadingScene()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~LoadingScene()
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

		/*
		次のシーンで使うリソースをこのシーンで読み込むので
		解放を行わないこと
		*/
	}

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();

private:
	// 変数宣言
	FONT font_;
	int value_;
	//非同期画像
	SPRITE asynchronous_image;

	SPRITE load_image;
	float load_alpa;
	int load_state;
	bool load_derite_flag;
	
	bool nextload_flag;
	float nextload_alpa;
	int nextload_state;
	int nextScene_;


	// 関数プロトタイプ

	void Next_Load_Fade();
};
