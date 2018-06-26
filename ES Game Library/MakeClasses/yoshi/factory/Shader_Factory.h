#pragma once
#include "../../../ESGLib.h"
#include "../effect/Shader.h"

class Shader_Factory
{
public:
	
	Shader* create()
	{
		return Factorymethod();
	}

	Shader_Factory();
	~Shader_Factory();

protected:

	virtual Shader* Factorymethod() = 0;

	


};
