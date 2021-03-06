#include "Noise.h"


Noise::Noise()
{

	noise_intensity = 0.7f;
	

}


Noise::~Noise()
{

}

bool Noise::Initialize()
{
	//ノイズ初期化
	offscreen = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	noise_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/Noise.fx"));
	return true;
}
void Noise::Update()
{

	noise_intensity = 0.7f;
	noise_effect->SetParameter("noise_intensity", noise_intensity);
	noise_effect->SetParameter("Time", Math_Random());

}
RENDERTARGET Noise::Go_Shader(RENDERTARGET srcRT)
{
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color_Black);

	//ノイズ条件
	
		//GraphicsDevice.RenderTargetToBackBuffer(nullptr, offscreen[0], nullptr);
		//GraphicsDevice.RenderTargetToRenderTarget(offscreen[1], offscreen[0], noise_effect);
	/*GraphicsDevice.
	();*/

		//描画状態を初期状態にする
		//SpriteBatch.InitTransform();

		////SpriteBatch_TopMostとは描画全面最優先にする
		//SpriteBatch.DrawSimple(*offscreen[1], Vector3(0.0f, 0.0f, SpriteBatch_TopMost), 0.5f);
	
	
	
	GraphicsDevice.RenderTargetToRenderTarget(offscreen, srcRT, noise_effect);
		/*GraphicsDevice.RenderTargetToRenderTarget(offscreen[2],offscreen[1],scan_effect);*/

	return offscreen;
}

void Noise::SetParameter(std::string parameter, float value)
{
	noise_effect->SetParameter(parameter.c_str(), value);
}


/*
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color_Black);*/
	////ノイズ条件
	//if (noise_time <= 0)
	//{
	//	GraphicsDevice.RenderTargetToBackBuffer(nullptr, offscreen[0], nullptr);
	//	GraphicsDevice.RenderTargetToRenderTarget(offscreen[1], offscreen[0], noise_effect);
	//	GraphicsDevice.SetDefaultRenderTarget();

	//	//描画状態を初期状態にする
	//	SpriteBatch.InitTransform();

	//	//SpriteBatch_TopMostとは描画全面最優先にする
	//	SpriteBatch.DrawSimple(*offscreen[1], Vector3(0.0f, 0.0f, SpriteBatch_TopMost), 0.5f);
	//} 
	//else
	//{
	//	GraphicsDevice.RenderTargetToRenderTarget(offscreen[1],offscreen[0],noise_effect);
	//	GraphicsDevice.RenderTargetToRenderTarget(offscreen[2],offscreen[1],scan_effect);

	//	GraphicsDevice.RenderTargetToBackBuffer(nullptr,offscreen[2],nullptr);
	//	SpriteBatch.DrawSimple(*offscreen[2], Vector3(0.0f, 0.0f, -100.0f), 1.0f);

	//}
//}
