#pragma once
#include "../../../ESGLib.h"
#include "Shader.h"

class Rester : public Shader
{
public:
	Rester();
	~Rester();
	
	RENDERTARGET offscreen[2];
	EFFECT rester_effect;

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);

	//ラスタースクロール
	float amplitude;
	float division;
	float distortion;
	int amplitude_state;
	int division_state;
	int distortion_state;

};

