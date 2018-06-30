#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"
#include "../MakeClasses/Fujimura/Judgement/JudgeCounter.h"

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
	// �ϐ��錾
	SPRITE  result_image;

	FONT score_font;
	FONT combo_font;
	FONT perfect_font;
	FONT great_font;
	FONT miss_font;
	
	//�ł΂΂�
	JudgeCounter counter_;
	int score_;
	int combo;
	int perfect;
	int great;
	int miss;

	//�����s����
	float load_alpa;
	int load_state;
	bool font_delete;
	


	// �֐��v���g�^�C�v

};
