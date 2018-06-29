#include "Combo.h"
#include "../../yoshi/effect/Effect_Singleton.h"


Combo::Combo(){

	this->combo_ = 0;

	this->numberSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_01.png"));
	this->textSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_text.png"));
	this->offscreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

}

Combo::~Combo(){

	GraphicsDevice.ReleaseRenderTarget(this->offscreen_);
}

void Combo::Update(){


}

void Combo::Draw(){

	//if (this->combo_ <= 0) return;

	Color color = Color(255, 255, 255);
	if (this->combo_ >= 50) color = Color(255, 0, 0);
	if (this->combo_ >= 100) color = Color(255, 255, 0);

	GraphicsDevice.SetRenderTarget(this->offscreen_);
	GraphicsDevice.Clear(Color(0,0,0,0));

	SpriteBatch.Begin();

		SpriteBatch.Draw(*this->numberSp_, Vector3(450.0f, 600.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f), 0.5f);

	SpriteBatch.End();

	RENDERTARGET onShaderScreen = this->offscreen_;
	std::vector<Effect_Singleton::SHADER_NAME> comand;
	comand.push_back(Effect_Singleton::blur);
	onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comand,onShaderScreen);

	GraphicsDevice.SetDefaultRenderTarget();

	SpriteBatch.Begin();

	SpriteBatch.Draw(*onShaderScreen,Vector3_Zero);

	SpriteBatch.End();

}

void Combo::ChangeCombo(JUDGE judge){

	if (judge == NONE) return;

	if (judge == MISS){
		this->combo_ = 0;
		for (auto method : this->comboBreakMethods_) method();
		return;
	}

	this->combo_++;

	for (auto methodPair : this->comboUpMethods_){
		if (methodPair.first(this->combo_)) methodPair.second();
	}

}

void Combo::NumberDraw(Vector3 pos,int number,Vector2 size){

}

void Combo::EntryComboUpMethod(ISRUN teams, NOTICE notice){
	std::pair<ISRUN, NOTICE> pair;
	pair.first = teams;
	pair.second = notice;

	this->comboUpMethods_.push_back(pair);
}

void Combo::EntryComboBreakMethod(NOTICE notice){
	this->comboBreakMethods_.push_back(notice);
}