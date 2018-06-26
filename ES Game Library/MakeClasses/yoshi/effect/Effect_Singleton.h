#pragma once
#include "../../../ESGLib.h"
#include <map>

class Shader;

class Effect_Singleton
{
public:
	
	enum SHADER_NAME
	{
		noise = 0,
		blur = 1,
		rester = 2,
		scan_line = 3,
		bloom = 4,

	};

	static Effect_Singleton& GetInstance()
	{
		static Effect_Singleton instance;
		return instance;

	}
	void Update();
	RENDERTARGET Image_On_Effect(std::vector<SHADER_NAME>&, RENDERTARGET);
	void SetParameter(SHADER_NAME shaderName,std::string parameterName,float value);
	
	~Effect_Singleton();
private:
	Effect_Singleton();
	Shader* create_shader(SHADER_NAME);
	//shader_aggregation=シェーダー集合体
	std::map<SHADER_NAME, Shader*>shader_aggregation;

};

