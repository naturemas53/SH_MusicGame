#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"

class Lane;
class EventLane;
class JudgementContext;
class UI;
class Dancer;

class GameMain : public CGameScene {
public:
	GameMain();

	virtual ~GameMain()
	{
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

		//GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		//GraphicsDevice.ReleaseAllEffects();

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;

private:

	// 変数宣言
	typedef std::pair<Lane*, JudgementContext*> LANESET;

	std::vector<LANESET> lanes_;
	std::pair<EventLane*, JudgementContext*> eventLane_;
	UI* ui_;
	SPRITE backLane_;
	Dancer* dancer_;
	float bgm_alpa;
	int bgm_state;
	bool bgm_flag;
	RENDERTARGET blackScreen_;

	int waitTime_;

	// 関数宣言
	void SpriteLoad();
	void Fade();
	void DataSave();

};
