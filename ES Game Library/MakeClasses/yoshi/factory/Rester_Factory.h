#pragma once
#include "../effect/Rester.h"
#include "../../../ESGLib.h"
#include "Shader_Factory.h"

class Rester_Factory : public Shader_Factory
{
public:

	Rester_Factory();
	~Rester_Factory();

protected:

	virtual Shader* Factorymethod();


};

