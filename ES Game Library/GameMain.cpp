// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include "MakeClasses\Fujimura\DataSingleton.h"
#include "MakeClasses\Fujimura\Judgement\JudgementContext.h"
#include "MakeClasses\Fujimura\Lane\Lane.h"
#include "MakeClasses\Fujimura\Lane\EventLane.h"
#include "MakeClasses\Fujimura\Note\Note\Note.h"
#include "MakeClasses\Fujimura\MusicScoreIO.h"
#include "MakeClasses\Fujimura\UI\UI.h"
#include "MakeClasses/Fujimura/MultiMouseDevice.h"
#include "MakeClasses\Fujimura\Dancer.h"
#include "MakeClasses\Fujimura\JukeBox.h"
#include <functional>

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>

GameMain :: GameMain() : DefaultFont(GraphicsDevice.CreateDefaultFont())
{
	this->SpriteLoad();

	this->ui_ = new UI();
	JUDGENOTICE notice = [this](JUDGE judge){
		ui_->NoticeJudge(judge);
	};

	this->dancer_ = new Dancer();

	std::vector<Lane*> laneInstances;

	LANESET laneset;
	laneset.second = new JudgementContext();
	laneset.second->EntryJudgeMethod(notice);
	laneset.first = new Lane(Vector3(320.0f - 72.0f, 720.0f - 190.0f, 0.0f), laneset.second, 0);
	laneInstances.push_back(laneset.first);
	this->lanes_.push_back(laneset);

	laneset.second = new JudgementContext();
	laneset.second->EntryJudgeMethod(notice);
	laneset.first = new Lane(Vector3(1280.0f - 320.0f - 72.0f, 720.0f - 190.0f, 0.0f), laneset.second, 1);
	laneInstances.push_back(laneset.first);
	this->lanes_.push_back(laneset);

	this->eventLane_.second = new JudgementContext();
	this->eventLane_.second->EntryJudgeMethod(notice);
	this->eventLane_.second->EntryJudgeMethod([this](JUDGE judge){
	
		switch (judge){
		case PERFECT: this->dancer_->SetPerformanceAnimation(); break;
		case MISS: this->dancer_->SetMissAnimation(); break;
		}
	
	});
	this->eventLane_.first = new EventLane(this->eventLane_.second);
	auto laneNotice = [this](BaseLane::VISITORMETHOD visitor){
		for (auto lane : this->lanes_){
			lane.first->Accept(visitor);
		}
	};
	this->eventLane_.first->EntryPostMethod(laneNotice);

	MusicScoreIO scoreIo("musicscore.txt");
	scoreIo.ImportScore(laneInstances, this->eventLane_.first);

	BgmComponent.LoadMusic(_T("music.wav"));
	BgmComponent.SetBPM(128);
	BgmComponent.Play();

	this->backLane_ = GraphicsDevice.CreateSpriteFromFile(_T("timing_bar.png"));
}

bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here



	for (auto laneset : this->lanes_){ 
		delete laneset.first;
		delete laneset.second;
	}

	delete this->eventLane_.first;
	delete this->eventLane_.second;

	delete this->ui_;

	delete this->dancer_;
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here
	DWORD nowTime = nowTime = BgmComponent.GetNowTime();

	this->eventLane_.first->Update(nowTime);
	for (auto laneset : this->lanes_) laneset.first->Update(nowTime);
	this->ui_->Update(nowTime);

	this->dancer_->Update(0);

	Effect_Singleton::GetInstance().Update();

	RawInputMouse mouse = MultiMouse.GetInputData(0);
	if (mouse.IsPushed(RIGHTBUTTON)){

		return GAME_SCENE(new TitleScene);

	}

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	DWORD nowTime = BgmComponent.GetNowTime();

	this->ui_->Draw(nowTime);

	GraphicsDevice.BeginAlphaBlend();
	this->dancer_->Draw(0);
	GraphicsDevice.EndAlphaBlend();

	SpriteBatch.Begin();
	SpriteBatch.Draw(*this->backLane_, Vector3_Zero, 1.0f);
	for (auto laneset : this->lanes_) laneset.first->Draw(nowTime);
	SpriteBatch.End();

	this->eventLane_.first->Draw(nowTime);

	GraphicsDevice.EndScene();
}

void GameMain::SpriteLoad(){

	Data.LoadAtlasSprite(_T("kari_atlas.png"));
	Data.LoadNormalNoteSprite(_T("Notes\\normal_notes.png"));
	Data.LoadLongNoteSprite(_T("Notes\\long_notes.png"));
	Data.LoadLongSquareSprite(_T("Notes\\long_notes_bar.png"));
	Data.LoadHeartSprite(_T("heart_drow.png"));
	Data.LoadJudgeSprite(_T("judges.png"));

}