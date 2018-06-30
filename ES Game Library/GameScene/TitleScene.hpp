#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"

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
	// �ϐ��錾

	FONT font_;
	SPRITE title_image;
	SPRITE click_image;
	SPRITE now_load_image;
	
	//�i�E���[�h�֘A
	float now_load_alpa;
	int  now_load_state;
	bool nou_load_flag;

	//�N���b�N�֘A
	float click_alpa;
	int click_state;
	bool click_delete;

	//�^�C�g���֘A
	int title_state;
	float title_alpa;


	// �֐��v���g�^�C�v
	//�����s����

	void Transparent();

};
