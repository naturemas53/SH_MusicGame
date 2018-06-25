#pragma once
#include "../../../ESGLib.h"
#include "Shader.h"

class Scan_Line : public Shader
{
public:
	Scan_Line();
	~Scan_Line();
private:

	EFFECT scan_effect;
	RENDERTARGET offscreen;
	int scan_parameter;
	
	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);


};

