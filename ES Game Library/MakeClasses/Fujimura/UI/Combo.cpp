#include "Combo.h"
#include "../../yoshi/effect/Effect_Singleton.h"
#include "../../Fujimura/BgmSingleton.h"
#include "../CalcUV.h"
#include "../BgmSingleton.h"
#include "IntValueDinamicScaleDraw.h"
#include "DinamicScaleInterface.h"


/*
1 ‰©F
2 —Î
3 Â
4 Ô
*/

Combo::Combo(float scale) : SCALE_(scale),
NUMBERSIZE_(Vector2(87.4f  *scale, 124.0f * scale)),
NUMBER_GROW_SIZE_(Vector2(87.4f * scale, 124.0f * scale)),
TEXTSIZE_(Vector2(232.0f * scale, 40.0f * scale)),
TEXT_GROW_SIZE_(Vector2(310.0f * scale, 118.0f * scale))
{

	this->combo_ = 0;

	this->numberSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_01.png"));
	this->numberGrowSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_02.png"));
	this->textSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_text.png"));
	this->textGrowSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_glow.png"));
	this->offscreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

	this->colors_.push_back(Color(255,255,0));
	this->colors_.push_back(Color(0,0,255));
	this->colors_.push_back(Color(0,255,0));
	this->colors_.push_back(Color(255,0,0));

	this->nowColor_ = this->colors_.begin();

	this->valueDraw_ = new IntValueDinamicScaleDraw(this->NUMBER_GROW_SIZE_,3);
	this->valueDraw_->Initialize();
	this->valueDraw_->AddScalePoint(0,Vector3(1.5f,1.5f,0.0f));
	this->valueDraw_->AddScalePoint(100,Vector3(1.0f,1.0f,0.0f));
	this->valueDraw_->Replay();

}

Combo::~Combo(){

	delete this->valueDraw_;
	GraphicsDevice.ReleaseRenderTarget(this->offscreen_);
}

void Combo::Update(){

	this->valueDraw_->Update();

}

void Combo::Draw(){

	if (this->combo_ <= 0) return;

	GraphicsDevice.SetRenderTarget(this->offscreen_);
	GraphicsDevice.Clear(Color(0,0,0,0));

	float numberWidth = this->NUMBER_GROW_SIZE_.x * 3.0f;
	float textWidth = this->TEXT_GROW_SIZE_.x;

	Vector2 textRivision = (this->TEXT_GROW_SIZE_ - this->TEXTSIZE_) / 2.0f;

	Vector3 basePos = Vector3(0.0f,535.0f,0.0f);

	SpriteBatch.Begin();

	Vector3 pos = basePos + Vector3((1280.0f - numberWidth) / 2.0f, 0.0f, 0.0f);

	this->valueDraw_->Draw(this->numberGrowSp_,pos,*(this->nowColor_),Vector2(87.4f,124.0f));
	this->valueDraw_->Draw(this->numberSp_,pos,Color(255,255,255),Vector2(87.4f,124.0f));

	SpriteBatch.End();


	RENDERTARGET onShaderScreen = this->offscreen_;

	CalcUV calcUV;
	float rhythmRate = BgmComponent.GetRhythmRate();
	if(rhythmRate / 0.5f >= 1.0f){
	
		rhythmRate = 1.0f - rhythmRate;

	}
	rhythmRate *= 2.0f;

	Effect_Singleton::GetInstance().SetParameter(Effect_Singleton::blur,"AddU",calcUV.CalcU(1.0f * rhythmRate));
	Effect_Singleton::GetInstance().SetParameter(Effect_Singleton::blur,"AddV",calcUV.CalcV(1.0f * rhythmRate));
	std::vector<Effect_Singleton::SHADER_NAME> comand;
	comand.push_back(Effect_Singleton::bloom);
	comand.push_back(Effect_Singleton::blur);
	onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comand,onShaderScreen);

	GraphicsDevice.SetDefaultRenderTarget();

	SpriteBatch.Begin();

	SpriteBatch.InitTransform();
	SpriteBatch.DrawSimple(*onShaderScreen,Vector3_Zero);
	pos = basePos + Vector3((1280.0f - textWidth) / 2.0f, this->NUMBER_GROW_SIZE_.y, 0.0f);
	SpriteBatch.Draw(*this->textSp_, pos + Vector3(textRivision.x,textRivision.y,0.0f) ,1.0f,Vector3_Zero,Vector3_Zero,this->SCALE_);
	SpriteBatch.Draw(*this->textGrowSp_, pos, *(this->nowColor_), Vector3_Zero, Vector3_Zero, this->SCALE_);

	SpriteBatch.End();

}

void Combo::ChangeCombo(JUDGE judge){

	if (judge == NONE) return;

	if (judge == MISS){
		this->combo_ = 0;
		this->valueDraw_->SetValue(0);
		for (auto method : this->comboBreakMethods_) method();
		return;
	}

	this->combo_++;
	this->valueDraw_->SetValue(this->combo_);

	for (auto methodPair : this->comboUpMethods_){
		if (methodPair.first(this->combo_)) methodPair.second();
	}

}

void Combo::NumberDraw(SPRITE sp,Vector3 pos,int number){

	Rect useRect = RectWH(87.0f * number,0,87.0f,124.0f);
	SpriteBatch.Draw(*sp,pos,useRect,1.0f,Vector3_Zero,Vector3_Zero,this->SCALE_);

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

void Combo::ChengeColor(){

	auto itr = this->colors_.end();
	itr--;
	if(this->nowColor_ != itr) this->nowColor_++;

}

void Combo::ColorReset(){	this->nowColor_ = this->colors_.begin(); }