#pragma once
#include "../../ESGLib.h"

class BgmSingleton{

public:

	~BgmSingleton();

	static BgmSingleton& GetInstance(){

		static BgmSingleton instance;
		return instance;

	}

	void LoadMusic(std::wstring path);

	void Play(int startTime = 0);

	void SetBPM(int bpm);

	float GetRhythmRate();
	DWORD GetNowTime(){ return this->bgm_->GetCurrentMilliSec(); }
	bool IsPlaying(){ return this->bgm_->IsPlaying(); }

private:

	BgmSingleton();

	SOUND bgm_;
	int bpm_;
	int rhythmTime_;

};

#define BgmComponent BgmSingleton::GetInstance()