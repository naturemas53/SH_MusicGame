#include "Effect_Singleton.h"
#include "Shader.h"
#include "../factory/Noise_Factory.h"

Effect_Singleton::Effect_Singleton()
{
	this->shader_aggregation[noise] = nullptr;
	this->shader_aggregation[blur] = nullptr;
	this->shader_aggregation[rester] = nullptr;
	this->shader_aggregation[scan_line] = nullptr;
	this->shader_aggregation[bloom] = nullptr;
}


Effect_Singleton::~Effect_Singleton()
{
	for (auto shader : this->shader_aggregation)
	{
		if (shader.second != nullptr) delete shader.second;

	}
}

void Effect_Singleton::Update()
{
	for (auto shader : this->shader_aggregation)
	{

		if (shader.second == nullptr) continue;
		shader.second->Update();

	}
}
void Effect_Singleton::SetParameter()
{

}


RENDERTARGET Effect_Singleton::Image_On_Effect(std::vector<SHADER_NAME>&Command_q, RENDERTARGET original_image)
{

	RENDERTARGET render;

	for (auto name : Command_q)
	{
		auto itr = this->shader_aggregation.find(name);
		if (itr == this->shader_aggregation.end()) continue;
		Shader* shader = (*itr).second;
		if (shader == nullptr)
		{
			shader = this->create_shader(name);
			this->shader_aggregation[name] = shader;
		}

		render = shader->Go_Shader(render);
	}

	return 0;
}

Shader* Effect_Singleton::create_shader(SHADER_NAME name)
{
	Shader* shader = nullptr;
	
	switch (name){
	case noise: shader = Noise_Factory().create();
	}

	return shader;
}


