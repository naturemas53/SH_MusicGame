#include "JukeBox.h"

JukeBox::JukeBox(){

	this->bgm_ = nullptr;
	this->bpm_ = 0;
	this->rhythmTime_ = 0;

}

JukeBox::~JukeBox(){


}

void JukeBox::LoadMusic(std::wstring path){
	this->bgm_ = SoundDevice.CreateSoundFromFile(const_cast<LPTSTR>(path.c_str()));
}

void JukeBox::Play(){ this->bgm_->Play(); }

float JukeBox::GetRhythmRate(){

	if (this->bpm_ <= 0) return 0.0f;

	DWORD nowTime = this->GetNowTime();
	int overbalance = (int)nowTime % this->rhythmTime_;

	return (float)overbalance / (float)this->rhythmTime_;

}

void JukeBox::SetBPM(int bpm){

	this->bpm_ = bpm;
	this->rhythmTime_ = (int)(60000.0f / (float)bpm);

}