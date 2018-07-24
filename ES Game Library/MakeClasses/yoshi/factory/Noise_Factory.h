#pragma once
#include "../../../ESGLib.h"
#include "..\effect\Shader.h"
#include "Shader_Factory.h"

class Noise_Factory : public Shader_Factory 
{
public:

	Noise_Factory();
	~Noise_Factory();
protected:
	virtual Shader* Factorymethod();
};

