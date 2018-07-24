#include "Rester.h"


Rester::Rester()
{

	//ラスタースクロール
	amplitude = 0.0f;
	division = 0.0f;
	distortion = 0.0f;
	amplitude_state = 0;
	division_state = 0;
	distortion_state = 0;



}


Rester::~Rester()
{
}
bool Rester::Initialize()
{
	offscreen[0] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	rester_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/Rester.fx"));
	return true;
}
void Rester::Update()
{
	//KeyboardState key_state = Keyboard->GetState();

	////ラスタースクロール計算ドラクエ旅の扉のようにうねうね
	//振幅
	//amplitude 
	//分割
	//division
	//ゆがみ
	//distortion 


	//各ラスターパラメーター適当なので使うならいい感じで！
	if (amplitude_state == 0)
	{
	
		amplitude += 0.01f;
		if (amplitude > 1.0f)
		{
			amplitude_state = 1;
		}

	
	}
	if (amplitude_state == 1)
	{
		amplitude -= 1.0f;

		if (amplitude <= -0.5)
		{
			amplitude_state = 0;
		}
	}

	rester_effect->SetParameter("amplitude", amplitude);

	if (division_state == 0)

	{
		division += 0.01f;

		if (division > 1.0f)
		{
			division_state = 1;
		}

	}

	if (division_state == 1)
	{
		division -= 0.01f;

		if (division <= -1.0f)
		{
			division_state = 0;
		}
	}

	rester_effect->SetParameter("division", division);

	if (distortion_state == 0)

	{
		distortion += 0.01f;

		if (distortion > 5.0f)
		{
			distortion_state = 1;
		}

	}

	if (distortion_state == 1)
	{
		distortion -= 0.01f;

		if (distortion <= -5.0)
		{
			distortion_state = 0;
		}

	}
	rester_effect->SetParameter("distortion", distortion);

}
	

RENDERTARGET Rester::Go_Shader(RENDERTARGET srcRT)
{

	GraphicsDevice.SetRenderTarget(offscreen[0]);
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.RenderTargetToRenderTarget(offscreen[0], srcRT, rester_effect);
	return offscreen[0];
}
void Rester::SetParameter(std::string parameter, float value)
{
	rester_effect->SetParameter(parameter.c_str(), value);

}
