/**
* @file WidthNoise.h
* @brief 横ノイズクラス
* @author So Fujimura
* @date 2018/07/20
*/
#pragma once
#include "../../yoshi/effect/Shader.h"
#include <random>

class WidthNoise : public Shader{

public:
	WidthNoise();
	~WidthNoise();

	virtual bool Initialize();
	virtual void Update();
	virtual RENDERTARGET Go_Shader(RENDERTARGET);
	virtual void SetParameter(std::string parameter, float value);

private:

	RENDERTARGET offScreen_;
	float time_;
	std::mt19937 random_;
	std::uniform_real_distribution<float> widthDist_;
	std::uniform_real_distribution<float> topHeightDist_;
	std::uniform_real_distribution<float> bottomHeightDist_;
	std::uniform_real_distribution<float> persentDist_;

};