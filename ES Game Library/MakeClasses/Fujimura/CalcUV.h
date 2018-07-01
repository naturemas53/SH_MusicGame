#pragma once

class CalcUV{

public:

	CalcUV() = default;
	~CalcUV() = default;

	float CalcU(float pixelValue){
	
		float onePixel = 1.0f / 1280.0f;
		return onePixel * pixelValue;

	};
	float CalcV(float pixelValue){
	
		float onePixel = 1.0f / 720.0f;
		return onePixel * pixelValue;
	
	}

private:

};