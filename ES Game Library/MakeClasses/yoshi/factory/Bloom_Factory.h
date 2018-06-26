#pragma once
#include "../../../ESGLib.h"
#include "../effect/Bloom.h"
#include "../effect/Shader.h"
#include "Shader_Factory.h"

class Bloom_Factory : public Shader_Factory
{
public:
	
	Bloom_Factory();
	~Bloom_Factory();
protected:
		virtual Shader* Factorymethod();
};

