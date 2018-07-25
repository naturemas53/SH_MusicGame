#pragma once
#include "NumberDrawInterface.h"
#include "DinamicScaleInterface.h"
#include "DinamicScaleCalculation.h"
#include <vector>

class NumberDinamicScaleDraw : public NumberDrawInterface,public DinamicScaleInterface{

public:

	NumberDinamicScaleDraw(Vector2 drawOneCellSize = Vector2_Zero);
	~NumberDinamicScaleDraw();


	virtual void Initialize();
	virtual void Update();
	virtual void Draw(SPRITE sprite, Vector3 drawPos, Color color, Vector2 imageOneCellSize);

	virtual int GetValue();
	virtual void SetValue(int value);

	virtual void Replay();

	virtual void AddScalePoint(int milliSecond, Vector3 Scale);
	virtual bool HasAddScalePoint(int milliSecond, Vector3 Scale);
	virtual void RemoveScalePoint(int milliSecond, Vector3 Scale);

private:

	const Vector2 DRAW_ONE_CELL_SIZE_;

	DinamicScaleCalculation scaleCalculation_;
	Vector2 nowScale_;

	int value_;

};