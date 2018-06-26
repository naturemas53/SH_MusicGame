#pragma once
#include "../../../ESGLib.h"
#include "Shader.h"


class Noise : public Shader
{

public:
	Noise();
	~Noise();

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);

private:

	EFFECT noise_effect;
	RENDERTARGET offscreen;
	float noise_intensity;
	int noise_time;

};

