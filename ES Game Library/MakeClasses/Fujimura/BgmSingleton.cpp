#include "BgmSingleton.h"

BgmSingleton::BgmSingleton(){

	this->bgm_ = nullptr;
	this->bpm_ = 0;
	this->rhythmTime_ = 0;

}

BgmSingleton::~BgmSingleton(){


}

void BgmSingleton::LoadMusic(std::wstring path){
	this->bgm_ = SoundDevice.CreateSoundFromFile(const_cast<LPTSTR>(path.c_str()));
}

void BgmSingleton::Play(int startTime){ 
	
	if(startTime > 0){
		this->bgm_->SetPlayPositionMilliSec(startTime);
	}
	this->bgm_->Play(); 

}

float BgmSingleton::GetRhythmRate(){

	if (this->bpm_ <= 0) return 0.0f;

	DWORD nowTime = this->GetNowTime();
	int overbalance = (int)nowTime % this->rhythmTime_;

	return (float)overbalance / (float)this->rhythmTime_;

	

}

void BgmSingleton::SetBPM(int bpm){

	this->bpm_ = bpm;
	this->rhythmTime_ = (int)(60000.0f / (float)bpm);

}