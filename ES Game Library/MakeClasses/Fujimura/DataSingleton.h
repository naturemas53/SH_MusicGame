#pragma once
#include "../../ESGLib.h"
#include <string>

class DataSingleton{

public:

	static DataSingleton& GetInstance(){

		static DataSingleton instance;
		return instance;

	}

	void LoadAtlasSprite(std::wstring path){
		this->atlasSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	void LoadNormalNoteSprite(std::wstring path){
		this->normalNoteSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	void LoadLongNoteSprite(std::wstring path){
		this->longNoteSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	void LoadLongSquareSprite(std::wstring path){
		this->longSquareSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str(),Color(255,255,254));
	}

	void LoadHeartSprite(std::wstring path){
		this->heartSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	void LoadJudgeSprite(std::wstring path){
		this->judgeSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	void LoadPerfectSprite(std::wstring path){
		this->perfectSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	void LoadGreatSprite(std::wstring path){
		this->greatSp_ = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	}

	~DataSingleton(){};

	SPRITE atlasSp_;
	SPRITE normalNoteSp_;
	SPRITE longNoteSp_;
	SPRITE longSquareSp_;
	SPRITE heartSp_;
	SPRITE judgeSp_;
	SPRITE perfectSp_;
	SPRITE greatSp_;
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