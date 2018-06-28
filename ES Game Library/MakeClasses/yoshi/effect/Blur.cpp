#include "Blur.h"


Blur::Blur()
{
	offscreen = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	blur_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/Blur.fx"));
	AddU = 0.0f;
	AddV = 0.0f;
	blur_state = 0;

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
	if (blur_state == 0)
	{
		AddU += 0.00019f;
		/*AddV += 0.001f;*/
		if (AddU >= 0.008)
		{
			blur_state = 1;
		}
	}

	if (blur_state == 1)
	{
		AddU -= 0.0009f;
		//AddV -= 0.001f;
		if (AddU <= 0)
		{
			blur_state = 0;
		}
	}

	blur_effect->SetParameter("AddU",AddU);
	blur_effect->SetParameter("AddV",AddU);
}

RENDERTARGET Blur::Go_Shader(RENDERTARGET srcRT)
{
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color(0,0,0,0));


	GraphicsDevice.RenderTargetToRenderTarget(offscreen, srcRT, blur_effect);

	return offscreen;
}

void Blur::SetParameter(std::string parameter, float value)
{
	blur_effect->SetParameter(parameter.c_str(), value);
}
