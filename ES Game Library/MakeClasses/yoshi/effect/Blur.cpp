#include "Blur.h"


Blur::Blur()
{
	offscreen = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	blur_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/Blur.fx"));

}


Blur::~Blur()
{
}
bool Blur::Initialize()
{
	return true;
}
void Blur::Update()
{

}

RENDERTARGET Blur::Go_Shader(RENDERTARGET srcRT)
{
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color_Black);

	



	GraphicsDevice.RenderTargetToRenderTarget(offscreen, srcRT, blur_effect);

	return offscreen;
}

void Blur::SetParameter(std::string parameter, float value)
{
	blur_effect->SetParameter(parameter.c_str(), value);
}
