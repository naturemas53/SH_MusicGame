#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"
#include "MakeClasses\Fujimura\FadeInOut.h"

class Lane;
class EventLane;
class JudgementContext;
class UI;
class Dancer;

class GameMain : public CGameScene {
public:
	GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
	{
		this->hasObjectInitialized_ = false;
	};

	virtual ~GameMain()
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

		//GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		//GraphicsDevice.ReleaseAllEffects();

	}

public:
	virtual bool Initialize();
	virtual bool ObjectInitialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;

private:

	// ïœêîêÈåæ
	bool hasObjectInitialized_;

	typedef std::pair<Lane*, JudgementContext*> LANESET;

	std::vector<LANESET> lanes_;
	std::pair<EventLane*, JudgementContext*> eventLane_;
	UI* ui_;
	SPRITE backLane_;
	SPRITE backLine_;
	Dancer* dancer_;

	int waitTime_;

	FadeInOut fade_;

	// ä÷êîêÈåæ
	void SpriteLoad();
	void DataSave();

};
