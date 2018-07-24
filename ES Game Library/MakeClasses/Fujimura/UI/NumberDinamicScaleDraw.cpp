#include "NumberDinamicScaleDraw.h"

NumberDinamicScaleDraw::NumberDinamicScaleDraw(Vector2 drawOneCellSize):
DRAW_ONE_CELL_SIZE_(drawOneCellSize){

	this->value_ = 0;

}

NumberDinamicScaleDraw::~NumberDinamicScaleDraw(){


}

void NumberDinamicScaleDraw::Initialize(){



}

void NumberDinamicScaleDraw::Update(){

	Vector3 scale = this->scaleCalculation_.UpdateScale(GameTimer.GetElapsedMilliSecond());

	this->nowScale_.x = scale.x;
	this->nowScale_.y = scale.y;

}

void NumberDinamicScaleDraw::Draw(SPRITE sprite, Vector3 drawPos, Color color, Vector2 imageOneCellSize){



}

int NumberDinamicScaleDraw::GetValue(){

	return 0;

}

void NumberDinamicScaleDraw::SetValue(int value){

}

void NumberDinamicScaleDraw::Replay(){

}

void NumberDinamicScaleDraw::SetScalePoint(int delayMilliSecond, Vector3 Scale){

}

bool NumberDinamicScaleDraw::IsAddedScalePoint(int delayMilliSecond, Vector3 Scale){
	return false;
}

void NumberDinamicScaleDraw::RemoveScalePoint(int delayMilliSecond, Vector3 Scale){

}