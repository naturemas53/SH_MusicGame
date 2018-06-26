#include "Blur_Factory.h"
#include "../effect/Blur.h"



Blur_Factory::Blur_Factory()
{
}


Blur_Factory::~Blur_Factory()
{
}

Shader* Blur_Factory::Factorymethod()
{
	return new Blur();
}
