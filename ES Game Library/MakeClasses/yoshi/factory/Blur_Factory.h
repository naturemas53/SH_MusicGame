#pragma once
#include "../effect/Blur.h"
#include "../../../ESGLib.h"
#include "Shader_Factory.h"
#include "../effect/Shader.h"

class Blur_Factory : public Shader_Factory
{
public:
	Blur_Factory();
	~Blur_Factory();

protected:
	virtual Shader* Factorymethod();
};

