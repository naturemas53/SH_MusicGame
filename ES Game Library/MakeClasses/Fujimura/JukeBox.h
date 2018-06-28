#pragma once
#include "../../ESGLib.h"

class JukeBox{

public:

	~JukeBox();

	static JukeBox& GetInstance(){

		static JukeBox instance;
		return instance;

	}

	void LoadMusic(std::wstring path);

	void Play();

	void SetBPM(int bpm);
	float GetRhythmRate();
	DWORD GetNowTime(){ return this->bgm_->GetCurrentMilliSec(); }
	bool IsPlaying(){ return this->bgm_->IsPlaying(); }

private:

	JukeBox();

	SOUND bgm_;
	int bpm_;
	int rhythmTime_;

};

#define BgmComponent JukeBox::GetInstance()