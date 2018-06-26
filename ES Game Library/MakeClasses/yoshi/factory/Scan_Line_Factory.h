#pragma once
#include "../../../ESGLib.h"
#include "../effect/Scan_Line.h"
#include "../effect/Shader.h"
#include "Shader_Factory.h"

class Scan_Line_Factory : public Shader_Factory
{
public:
	
	Scan_Line_Factory();
	~Scan_Line_Factory();

protected:

	virtual Shader* Factorymethod();

private:

};

