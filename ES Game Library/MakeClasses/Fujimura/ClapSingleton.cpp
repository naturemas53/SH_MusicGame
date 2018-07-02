#include "ClapSingleton.h"

ClapSingleton::ClapSingleton(){

}

void ClapSingleton::LoadClap(){

	this->clapSounds_[JUDGE::PERFECT] = SoundDevice.CreateSoundFromFile(_T("ClapSounds/perfect.wav"));
	this->clapSounds_[JUDGE::GREAT] = SoundDevice.CreateSoundFromFile(_T("ClapSounds/great.wav"));
	this->clapSounds_[JUDGE::MISS] = SoundDevice.CreateSoundFromFile(_T("ClapSounds/miss.wav"));

	this->eventClapSounds_[JUDGE::PERFECT] = SoundDevice.CreateSoundFromFile(_T("ClapSounds/event_perfect.wav"));
	//this->eventClapSounds_[JUDGE::MISS] = SoundDevice.CreateSoundFromFile(_T("ClapSounds/"));

}

ClapSingleton::~ClapSingleton(){



}

void ClapSingleton::PlayClap(JUDGE judge){

	auto itr = this->clapSounds_.find(judge);
	if (itr == this->clapSounds_.end()) return;

	(*itr).second->Play();

}

void ClapSingleton::PlayEventClap(JUDGE judge){

	auto itr = this->eventClapSounds_.find(judge);
	if (itr == this->eventClapSounds_.end()) return;

	(*itr).second->Play();

}