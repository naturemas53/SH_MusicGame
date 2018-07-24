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

	//GraphicsDevice.RenderTargetToBackBuffer(nullptr, offscreen[0], nullptr);
	//GraphicsDevice.RenderTargetToRenderTarget(offscreen[1], offscreen[0], scan_effect);
	//GraphicsDevice.SetDefaultRenderTarget();

	//•`‰æó‘Ô‚ğ‰Šúó‘Ô‚É‚·‚é
	//SpriteBatch.InitTransform();

	////SpriteBatch_TopMost‚Æ‚Í•`‰æ‘S–ÊÅ—Dæ‚É‚·‚é
	//SpriteBatch.DrawSimple(*offscreen[1], Vector3(0.0f, 0.0f, SpriteBatch_TopMost), 0.5f);

	GraphicsDevice.RenderTargetToRenderTarget(offscreen_scan, srcRT, scan_effect);
	return offscreen_scan;



	//GraphicsDevice.RenderTargetToRenderTarget(offscreen[1], offscreen[0], scan_effect);
	///*GraphicsDevice.RenderTargetToRenderTarget(offscreen[2],offscreen[1],scan_effect);*/

	//GraphicsDevice.RenderTargetToBackBuffer(nullptr, offscreen[1], nullptr);
	////SpriteBatch.DrawSimple(*offscreen[1], Vector3(0.0f, 0.0f, -100.0f), 1.0f);
	//return offscreen;
}

void Scan_Line::SetParameter(std::string parameter, float value)
{
	scan_effect->SetParameter(parameter.c_str(), value);
}
