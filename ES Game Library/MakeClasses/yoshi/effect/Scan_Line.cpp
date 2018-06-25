#include "Scan_Line.h"


Scan_Line::Scan_Line()
{
	////‘–¸ü‰Šú‰»
	scan_effect = GraphicsDevice.CreateEffectFromFile(_T("FX/Scan_line.Fx"));
	//scan_parameter = 1000;
	offscreen = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	scan_parameter = 1;

	
}


Scan_Line::~Scan_Line()
{
}
bool Scan_Line::Initialize()
{
	return true;
}
void Scan_Line::Update()
{
	scan_parameter += 1;
	scan_effect->SetParameter("Time", scan_parameter);
}
RENDERTARGET Scan_Line::Go_Shader(RENDERTARGET srcRT)
{
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color_Black);

	//GraphicsDevice.RenderTargetToBackBuffer(nullptr, offscreen[0], nullptr);
	//GraphicsDevice.RenderTargetToRenderTarget(offscreen[1], offscreen[0], scan_effect);
	//GraphicsDevice.SetDefaultRenderTarget();

	//•`‰æó‘Ô‚ğ‰Šúó‘Ô‚É‚·‚é
	//SpriteBatch.InitTransform();

	////SpriteBatch_TopMost‚Æ‚Í•`‰æ‘S–ÊÅ—Dæ‚É‚·‚é
	//SpriteBatch.DrawSimple(*offscreen[1], Vector3(0.0f, 0.0f, SpriteBatch_TopMost), 0.5f);

	GraphicsDevice.RenderTargetToRenderTarget(offscreen, srcRT, scan_effect);
	return offscreen;



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
