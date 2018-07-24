#pragma once
#include "IntValueDrawInterface.h"
#include <vector>

class NumberDrawInterface;

class IntValueDinamicScaleDraw : public IntValueDrawInterface{

public:
	IntValueDinamicScaleDraw(Vector2 drawOneCellSize = Vector2_Zero,int numLength = 1);
	~IntValueDinamicScaleDraw();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw(SPRITE sprite, Vector3 drawPos, Color color ,Vector2 imageOneCellSize);

	virtual int GetValue(){
		return this->value_;
	}

	virtual void SetValue(int value);

private:

	int value_;
	int numLength_;

	std::vector<NumberDrawInterface*> numberDraws_;

};