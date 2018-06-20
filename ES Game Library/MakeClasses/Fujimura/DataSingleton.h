#pragma once
#include "../../ESGLib.h"
#include <string>

class DataSingleton{

public:

	static DataSingleton& GetInstance(){

		static DataSingleton instance;
		return instance;

	}

	void LoadSprite(std::wstring path){
		this->atlasSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	~DataSingleton(){};

	SPRITE atlasSp_;
	const Vector2 NOTESIZE_;
	const Rect SINGLENOTERECT_;
	const Rect LONGNOTERECT_;
	const Rect EVENTNOTERECT_;

	const int NORMCOMBO_;

	const int LONG_OK_RELEASE_TIME_;

	const int BOMB_MAX_PAL_VALUE_;

private:

	DataSingleton();

};

#define Data DataSingleton::GetInstance()