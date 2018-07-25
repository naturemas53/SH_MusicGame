#pragma once
#include "IntValueDrawInterface.h"
#include "NumberDinamicScaleDraw.h"
#include "DinamicScaleInterface.h"
#include <vector>

class NumberDrawInterface;

class IntValueDinamicScaleDraw : public IntValueDrawInterface,public DinamicScaleInterface{

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

	virtual void Replay();

	virtual void AddScalePoint(int milliSecond,Vector3 scale);
	virtual bool HasAddScalePoint(int milliSecond, Vector3 scale);
	virtual void RemoveScalePoint(int milliSecond, Vector3 scale);

private:

	const Vector2 DRAW_ONE_CELL_SIZE_;

	int value_;
	int numLength_;

	std::vector<NumberDinamicScaleDraw*> numberDraws_;

};