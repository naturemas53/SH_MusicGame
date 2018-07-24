#pragma once
#include "../UI/IntValueDrawInterface.h"

class IntValueSimpleDraw : public IntValueDrawInterface{

public:

	IntValueSimpleDraw(Vector2 drawOneCellSize = Vector2_Zero) : 
		DRAW_ONE_CELL_SIZE_(drawOneCellSize){ 

		this->value_ = 0;

	};
	~IntValueSimpleDraw(){};

	virtual void Initialize(){};
	virtual void Update(){};
	virtual void Draw(SPRITE sprite, Vector3 drawPos,Color color, Vector2 imageOneCellSize);

	virtual int GetValue(){ return this->value_; }
	virtual void SetValue(int value){ this->value_ = value; }

private:

	const Vector2 DRAW_ONE_CELL_SIZE_;
	int value_;

};