#include "Bloom_Factory.h"
#include "../effect/Bloom.h"



Bloom_Factory::Bloom_Factory()
{
}


Bloom_Factory::~Bloom_Factory()
{
}
Shader* Bloom_Factory::Factorymethod()
{
	return new Bloom();
}
