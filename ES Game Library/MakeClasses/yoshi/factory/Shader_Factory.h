#pragma once
#include "../../../ESGLib.h"
#include "../effect/Shader.h"

class Shader_Factory
{
public:
	
	Shader* create()
	{
		return Factorymethod();
	}

	Shader_Factory();
	~Shader_Factory();

protected:

	virtual Shader* Factorymethod() = 0;

	


};
//class Noise_Factory : Shader_Factory
//{
//	virtual void method1() = 0;
//	virtual void method2() = 0;
//};
//class Rester_Factory : Shader_Factory
//{
//
//};
//class Bloom_Factory : Shader_Factory
//{
//	
//};
//class Scan_LIne_Factory : Shader_Factory
//{
//	
//};
