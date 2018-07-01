#include "Combo.h"
#include "../../yoshi/effect/Effect_Singleton.h"
#include "../../Fujimura/JukeBox.h"


Combo::Combo(float scale) : SCALE_(scale),
NUMBERSIZE_(Vector2(87.0f  *scale, 124.0f * scale)),
NUMBER_GROW_SIZE_(Vector2(87.0f * scale, 124.0f * scale)),
TEXTSIZE_(Vector2(232.0f * scale, 40.0f * scale)),
TEXT_GROW_SIZE_(Vector2(310.0f * scale, 118.0f * scale))
{

	this->combo_ = 0;

	this->numberSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_01.png"));
	this->numberGrowSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_02.png"));
	this->textSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_text.png"));
	this->textGrowSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_glow.png"));
	this->offscreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

}

Combo::~Combo(){

	GraphicsDevice.ReleaseRenderTarget(this->offscreen_);
}

void Combo::Update(){


}

void Combo::Draw(){

	//if (this->combo_ <= 0) return;

	Color color = Color(255, 255, 0);
	if (this->combo_ >= 50) color = Color(255, 0, 0);
	if (this->combo_ >= 100) color = Color(255, 255, 0);

	GraphicsDevice.SetRenderTarget(this->offscreen_);
	GraphicsDevice.Clear(Color(0,0,0,0));

	float numberWidth = this->NUMBER_GROW_SIZE_.x * 3.0f;
	float textWidth = this->TEXT_GROW_SIZE_.x;

	Vector2 textRivision = (this->TEXT_GROW_SIZE_ - this->TEXTSIZE_) / 2.0f;

	Vector3 basePos = Vector3(0.0f,570.0f,0.0f);

	SpriteBatch.Begin();

	Vector3 pos = basePos + Vector3((1280.0f - numberWidth) / 2.0f, 0.0f, 0.0f);

	int j = 0;
	for (int i = 100; i > 0; i /= 10){
		{
			int number = (this->combo_ / i) % 10;
			Vector3 numberPos = pos + Vector3(this->NUMBERSIZE_.x * j, 0.0f, 0.0f);
			this->NumberDraw(this->numberSp_, numberPos, number);
			this->NumberDraw(this->numberGrowSp_, numberPos, number);
			j++;
		}
	}

	pos = basePos + Vector3((1280.0f - textWidth) / 2.0f, this->NUMBER_GROW_SIZE_.y - 15.0f, 0.0f);
	SpriteBatch.Draw(*this->textGrowSp_, pos, color, Vector3_Zero, Vector3_Zero, this->SCALE_);

	pos += Vector3(textRivision.x,textRivision.y,0.0f);
	SpriteBatch.Draw(*this->textSp_, pos ,1.0f,Vector3_Zero,Vector3_Zero,this->SCALE_);

	SpriteBatch.End();


	RENDERTARGET onShaderScreen = this->offscreen_;

	std::vector<Effect_Singleton::SHADER_NAME> comand;
	//comand.push_back(Effect_Singleton::bloom);
	comand.push_back(Effect_Singleton::blur);
	onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comand,onShaderScreen);

	GraphicsDevice.SetDefaultRenderTarget();

	SpriteBatch.Begin();

	SpriteBatch.InitTransform();
	SpriteBatch.DrawSimple(*onShaderScreen,Vector3_Zero);

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