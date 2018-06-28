#include "Combo.h"
#include "../../yoshi/effect/Effect_Singleton.h"


Combo::Combo(){

	this->combo_ = 0;
	this->font_ = GraphicsDevice.CreateDefaultFont();

	//画像テスト

	combo_image = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/conbo_number_02.png"));
	offscreen[0] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	offscreen[1] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);




}

Combo::~Combo(){


}

void Combo::Update(){


}

void Combo::Draw(){

	if (this->combo_ <= 0) return;

	Color color = Color(255, 255, 255);
	if (this->combo_ >= 50) color = Color(255, 0, 0);
	if (this->combo_ >= 100) color = Color(255, 255, 0);

	GraphicsDevice.SetRenderTarget(offscreen[0]);
	GraphicsDevice.Clear(Color(0,0,0,0));

	//画像テスト
	SpriteBatch.Begin();

	SpriteBatch.DrawString(this->font_,Vector2_Zero,color,_T("%d Combo"),this->combo_);

	SpriteBatch.Draw(*combo_image, Vector3(450.0f,600.0f, 0.0f), 1.0f, Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f), 0.5f);


	//450.0f, 600.0f, 0.0f 本来の座標
	//転送終わり
	SpriteBatch.End();

	std::vector<Effect_Singleton::SHADER_NAME> comands_;
	comands_.push_back(Effect_Singleton::blur);
	comands_.push_back(Effect_Singleton::bloom);
	RENDERTARGET unko = Effect_Singleton::GetInstance().Image_On_Effect(comands_, offscreen[0]);

	

	//GraphicsDevice.RenderTargetToBackBuffer(Rect(450.0f, 600.0f, 1280.0f, 720.0f), offscreen[1],
	//	Rect(450.0f, 600.0f, 1280.0f, 720.0f));


	GraphicsDevice.SetDefaultRenderTarget();

//	GraphicsDevice.BeginAlphaBlend();

	SpriteBatch.Begin();

	GraphicsDevice.SetBlendMode(BlendMode_Add);

	/*画像,座標 転送元領域 透明度 回転 中心 スケール*/
		
	SpriteBatch.Draw(*unko, Vector3(450.0f, 600.0f, 0.0f),
		Rect(450.0f, 600.0f, 900.0f, 680.0f),0.5f,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	
	SpriteBatch.End();

//	GraphicsDevice.EndAlphaBlend();

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

void Combo::EntryComboUpMethod(ISRUN teams, NOTICE notice){
	std::pair<ISRUN, NOTICE> pair;
	pair.first = teams;
	pair.second = notice;

	this->comboUpMethods_.push_back(pair);
}

void Combo::EntryComboBreakMethod(NOTICE notice){
	this->comboBreakMethods_.push_back(notice);
}