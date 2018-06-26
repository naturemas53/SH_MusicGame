#pragma once
#include "../../../ESGLib.h"
#include "Shader.h"

class Blur : public Shader
{
public:
	Blur();
	~Blur();

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);

private:

	EFFECT blur_effect;
	RENDERTARGET offscreen;
	
};




