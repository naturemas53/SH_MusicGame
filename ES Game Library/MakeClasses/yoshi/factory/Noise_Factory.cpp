#include "Noise_Factory.h"
#include "../effect/Noise.h"


Noise_Factory::Noise_Factory()
{
}


Noise_Factory::~Noise_Factory()
{
}

Shader* Noise_Factory::Factorymethod()
{
	return new Noise();
}
