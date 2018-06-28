#include "Bloom.h"


Bloom::Bloom()
{
	offscreen[0] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	offscreen[1] = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

	bloom_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/HDR.fx"));
	
}


Bloom::~Bloom()
{
}
bool Bloom::Initialize()
{
	return true;
}
void Bloom::Update()
{
	
}
RENDERTARGET Bloom::Go_Shader(RENDERTARGET srcRT)
{
	const float bloom_rect = 256.0;
	GraphicsDevice.SetRenderTarget(offscreen[0]);
	GraphicsDevice.Clear(Color(0,0,0,0));

	bloom_effect->SetTechnique("Bright");
	bloom_effect->SetParameter("MinBright", -5.0f);
	GraphicsDevice.RenderTargetToRenderTarget(offscreen[0], srcRT, bloom_effect);

	
	//450.0f, 600.0f
	//830
	

	////213�s��_��x�ڂ̃��N�g�œ]���̈�̎w��(�E�[�j�A���̌�ݒ�悩���ʂւ̓]���̈�ւ̎w��B
	//GraphicsDevice.RenderTargetToBackBuffer(Rect(1280 - bloom_rect, 0, 1280, 720), offscreen, Rect(1280 - test, 0, 1280, 720));

	
	//GraphicsDevice.SetDefaultRenderTarget();

	return offscreen[0];
}
void Bloom::SetParameter(std::string parameter, float value)
{
	bloom_effect->SetParameter(parameter.c_str(), value);

}

