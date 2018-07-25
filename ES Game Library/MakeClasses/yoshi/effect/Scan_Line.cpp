#include "Scan_Line.h"


Scan_Line::Scan_Line()
{
	////‘–¸ü‰Šú‰»
	//scan_parameter = 1000;
	Time = 500;

	
}
Scan_Line::~Scan_Line()
{
}

bool Scan_Line::Initialize()
{
	offscreen_scan = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	scan_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/Scan_line.Fx"));
	return true;
}
void Scan_Line::Update()
{
	Time += 100;
	scan_effect->SetParameter("Time",Time);

}
RENDERTARGET Scan_Line::Go_Shader(RENDERTARGET srcRT)
{
	GraphicsDevice.SetRenderTarget(offscreen_scan);
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.RenderTargetToRenderTarget(offscreen_scan, srcRT, scan_effect);
	return offscreen_scan;

}

void Scan_Line::SetParameter(std::string parameter, float value)
{
	scan_effect->SetParameter(parameter.c_str(), value);
}
