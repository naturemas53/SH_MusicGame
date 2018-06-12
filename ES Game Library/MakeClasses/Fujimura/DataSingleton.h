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

	~DataSingleton();

	SPRITE atlasSp_;
	const Vector2 NOTESIZE_ = Vector2(64.0f, 32.0f);
	const Rect SINGLENOTERECT_ = RectWH(0, 100, 64, 32);
	const Rect LONGNOTERECT_ = RectWH(0, 100, 64, 32);
	const Rect EVENTNOTERECT_ = RectWH(0, 100, 64, 32);
	const int NORMCOMBO_ = 50;

private:

	DataSingleton(){
	
		this->atlasSp_ = nullptr;

	};

};

#define Data DataSingleton::GetInstance();