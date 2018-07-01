#include "Effect_Singleton.h"
#include "Shader.h"
#include "../factory/Noise_Factory.h"
#include "../factory/Scan_Line_Factory.h"
#include "../factory/Blur_Factory.h"
#include "../factory/Rester_Factory.h"
#include "../factory/Bloom_Factory.h"

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
	//シェーダーアップデート呼び出す
	for (auto shader : this->shader_aggregation)
	{

		if (shader.second == nullptr) continue;
		shader.second->Update();

	}
}
void Effect_Singleton::SetParameter(SHADER_NAME shaderName, std::string parameterName, float value)
{
	auto itr = this->shader_aggregation.find(shaderName);
	if (itr == this->shader_aggregation.end()) return;
	if ((*itr).second == nullptr){
		(*itr).second = this->create_shader(shaderName);
	}

	(*itr).second->SetParameter(parameterName,value);

}


RENDERTARGET Effect_Singleton::Image_On_Effect(std::vector<SHADER_NAME>&Command_q, RENDERTARGET original_image)
{

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

		original_image = shader->Go_Shader(original_image);
	}

	return original_image;
}

Shader* Effect_Singleton::create_shader(SHADER_NAME name)
{
	Shader* shader = nullptr;
	
	switch (name)
	{

		case noise: shader = Noise_Factory().create(); break;
		case scan_line: shader = Scan_Line_Factory().create(); break;
		case blur: shader = Blur_Factory().create(); break;
		case rester: shader = Rester_Factory().create(); break;
		case bloom: shader = Bloom_Factory().create(); break;

	}

	return shader;
}


