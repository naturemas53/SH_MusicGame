#include "LaneManager.h"
#include "Lane.h"
#include "../MusicScoreIO.h"
#include <functional>

class Note;

LaneManager::LaneManager(MusicScoreIO* io){

	std::vector<std::function<void(Note*)> > addMethods;

	Lane* lane;
	for (int i = 0; i < 2;i++){

		lane = new Lane(nullptr,Vector3(i * 640.0f,0.0f,0.0f));
		addMethods.push_back([&](Note* note){ lane->AddNote(note); });
		this->lanes_.push_back(lane);
	}

	io->ImportScore(addMethods);

}

LaneManager::~LaneManager(){

	for (auto lane : this->lanes_) delete lane;

}

void LaneManager::Update(DWORD nowTime){

	for (UINT i = 0; i < this->lanes_.size(); i++){



	}

}

void LaneManager::Draw(DWORD nowTime){

	for (auto lane : this->lanes_) lane->Draw(nowTime);

}

void LaneManager::EntryUI(UI* ui){ this->ui_ = ui; }