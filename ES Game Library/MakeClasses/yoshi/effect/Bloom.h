#pragma once
#include "../../../ESGLib.h"
#include "Shader.h"
class Bloom : public Shader
{
public:
	Bloom();
	~Bloom();

	RENDERTARGET offscreen[2];
	EFFECT bloom_effect;

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);
	float MinBright;
	int min_state;

};

