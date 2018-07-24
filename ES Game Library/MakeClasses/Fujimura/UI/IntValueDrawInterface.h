#pragma once
#include "../../../ESGLib.h"

class IntValueDrawInterface{

public:
	IntValueDrawInterface(){};
	virtual ~IntValueDrawInterface(){};

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw(SPRITE sprite,Vector3 drawPos,Color color,Vector2 imageOneCellSize) = 0;

	virtual int GetValue() = 0;
	virtual void SetValue(int value) = 0;

};