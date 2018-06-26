#pragma once
#include "../../../ESGLib.h"


class Shader
{
public:
	Shader();
	~Shader();

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter,float value);

};

