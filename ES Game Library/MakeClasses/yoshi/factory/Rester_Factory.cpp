#include "Rester_Factory.h"
#include "../effect/Rester.h"



Rester_Factory::Rester_Factory()
{
}


Rester_Factory::~Rester_Factory()
{
}
Shader* Rester_Factory::Factorymethod()
{
	return new Rester();
}

