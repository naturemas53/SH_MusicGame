#include "Rester.h"


Rester::Rester()
{
}


Rester::~Rester()
{
}
bool Rester::Initialize()
{
	return true;
}
void Rester::Update()
{

}
RENDERTARGET Rester::Go_Shader(RENDERTARGET)
{
	return 0;
}
void Rester::SetParameter(std::string parameter, float value)
{
	rester_effect->SetParameter(parameter.c_str(), value);

}
