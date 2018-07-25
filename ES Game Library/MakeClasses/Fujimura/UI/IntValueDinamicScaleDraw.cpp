#include "IntValueDinamicScaleDraw.h"

IntValueDinamicScaleDraw::IntValueDinamicScaleDraw(Vector2 drawOneCellSize,int numLength):
DRAW_ONE_CELL_SIZE_(drawOneCellSize){

	this->numLength_ = numLength;
	this->value_ = 0;

}

IntValueDinamicScaleDraw::~IntValueDinamicScaleDraw(){

	for(auto data:this->numberDraws_){
	
		delete data;

	}

}

void IntValueDinamicScaleDraw::Initialize(){

	for(int i = 0; i < this->numLength_;i++){

		NumberDinamicScaleDraw* numberDraw = new NumberDinamicScaleDraw(this->DRAW_ONE_CELL_SIZE_);
		numberDraw->Initialize();
		this->numberDraws_.push_back(numberDraw);

	}

}

void IntValueDinamicScaleDraw::Update(){

	if(this->numberDraws_.size() == 0) return;

	for(auto data:this->numberDraws_){
	
		data->Update();

	}

}

void IntValueDinamicScaleDraw::Draw(SPRITE sprite, Vector3 drawPos, Color color,Vector2 imageOneCellSize){

	if(this->numberDraws_.size() == 0) return;


	for(int i = 0;i < this->numberDraws_.size();i++){
	
		this->numberDraws_[i]->Draw(sprite,drawPos,color,imageOneCellSize);
		drawPos.x += this->DRAW_ONE_CELL_SIZE_.x;

	}

}

void IntValueDinamicScaleDraw::SetValue(int value){

	this->value_ = value;

	int i = 1;
	for(int j = 0;j < this->numLength_ - 1;i *= 10,j++);

	for(int j = 0;j < this->numberDraws_.size();j++){
	
		int number =  value / i % 10;

		i /= 10;
		if(this->numberDraws_[j]->GetValue() == number){
		
			continue;

		}

		this->numberDraws_[j]->SetValue( number );
		this->numberDraws_[j]->Replay();

	}

}

void IntValueDinamicScaleDraw::Replay(){

	for(auto data:this->numberDraws_){
	
		data->Replay();

	}

}

void IntValueDinamicScaleDraw::AddScalePoint(int milliSecond,Vector3 scale){

	for(auto data:this->numberDraws_){
	
		data->AddScalePoint(milliSecond,scale);

	}

}

bool IntValueDinamicScaleDraw::HasAddScalePoint(int milliSecond,Vector3 scale){

	for(auto data:this->numberDraws_){
	
		if(data->HasAddScalePoint(milliSecond,scale)){
		
			return true;
		
		}

	}

	return false;

}

void IntValueDinamicScaleDraw::RemoveScalePoint(int milliSecond,Vector3 scale){

	for(auto data:this->numberDraws_){
	
		data->RemoveScalePoint(milliSecond,scale);

	}

}