#include "Scan_Line_Factory.h"
#include "../effect/Scan_Line.h"



Scan_Line_Factory::Scan_Line_Factory()
{
}


Scan_Line_Factory::~Scan_Line_Factory()
{
}
Shader* Scan_Line_Factory::Factorymethod()
{
	return new Scan_Line();
}
