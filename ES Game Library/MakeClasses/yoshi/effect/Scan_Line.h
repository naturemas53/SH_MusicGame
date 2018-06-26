#pragma once
#include "../../../ESGLib.h"
#include "Shader.h"

class Scan_Line : public Shader
{
public:
	Scan_Line();
	~Scan_Line();

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);

private:

	EFFECT scan_effect;
	RENDERTARGET offscreen_scan;
	float Time;
	


};

