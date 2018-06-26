#include "Bloom.h"


Bloom::Bloom()
{
}


Bloom::~Bloom()
{
}
bool Bloom::Initialize()
{
	return true;
}
void Bloom::Update()
{

}
RENDERTARGET Bloom::Go_Shader(RENDERTARGET)
{
	return 0;
}
void Bloom::SetParameter(std::string parameter, float value)
{
	bloom_effect->SetParameter(parameter.c_str(), value);

}

