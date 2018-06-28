#pragma once
#include "../effect/Rester.h"
#include "../../../ESGLib.h"
#include "Shader_Factory.h"
#include "../effect/Shader.h"

class Rester_Factory : public Shader_Factory
{
public:

	Rester_Factory();
	~Rester_Factory();

protected:

	virtual Shader* Factorymethod();


};

