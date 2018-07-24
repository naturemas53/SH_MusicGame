#include "Noise_Factory.h"
//#include "../effect/Noise.h"
#include "../../Fujimura/Shader/WidthNoise.h"


Noise_Factory::Noise_Factory()
{
}


Noise_Factory::~Noise_Factory()
{
}

Shader* Noise_Factory::Factorymethod()
{
	return new WidthNoise();
}
