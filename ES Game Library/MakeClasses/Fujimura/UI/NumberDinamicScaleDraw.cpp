#include "NumberDinamicScaleDraw.h"

NumberDinamicScaleDraw::NumberDinamicScaleDraw(Vector2 drawOneCellSize) :
DRAW_ONE_CELL_SIZE_(drawOneCellSize)
{

	this->value_ = 0;
	this->nowScale_ = Vector2_One;

}

NumberDinamicScaleDraw::~NumberDinamicScaleDraw(){


}

void NumberDinamicScaleDraw::Initialize(){

	this->scaleCalculation_.Initialize();

}

void NumberDinamicScaleDraw::Update(){

	Vector3 scale = this->scaleCalculation_.UpdateScale(GameTimer.GetElapsedMilliSecond());

	this->nowScale_.x = scale.x;
	this->nowScale_.y = scale.y;

}

void NumberDinamicScaleDraw::Draw(SPRITE sprite, Vector3 drawPos, Color color, Vector2 imageOneCellSize){

	Rect rect = RectWH(this->value_ * imageOneCellSize.x,0,imageOneCellSize.x,imageOneCellSize.y);

	Vector2 scale;
	scale.x = this->DRAW_ONE_CELL_SIZE_.x / imageOneCellSize.x;
	scale.y = this->DRAW_ONE_CELL_SIZE_.y / imageOneCellSize.y;

	scale.x *= this->nowScale_.x;
	scale.y *= this->nowScale_.y;

	Vector2 numberRivision = (this->DRAW_ONE_CELL_SIZE_ - imageOneCellSize) / 2.0f;
	drawPos.x += numberRivision.x;

	SpriteBatch.Draw(*sprite,drawPos,rect,color,Vector3_Zero,Vector3(imageOneCellSize.x / 2.0f,imageOneCellSize.y / 2.0f,0.0f),scale);

}

int NumberDinamicScaleDraw::GetValue(){

	return this->value_;

}

void NumberDinamicScaleDraw::SetValue(int value){

	this->value_ = value % 10;

}

void NumberDinamicScaleDraw::Replay(){

	this->scaleCalculation_.Replay();

}

void NumberDinamicScaleDraw::AddScalePoint(int milliSecond, Vector3 scale){

	this->scaleCalculation_.AddScalePoint(milliSecond,scale);

}

bool NumberDinamicScaleDraw::HasAddScalePoint(int milliSecond, Vector3 scale){

	return this->scaleCalculation_.HasAddScalePoint(milliSecond,scale);

}

void NumberDinamicScaleDraw::RemoveScalePoint(int milliSecond, Vector3 scale){

	this->scaleCalculation_.RemoveScalePoint(milliSecond,scale);

}