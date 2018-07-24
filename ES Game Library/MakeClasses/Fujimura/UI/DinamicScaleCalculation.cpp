#include "DinamicScaleCalculation.h"

DinamicScaleCalculation::DinamicScaleCalculation(){

	this->totalElapsedMilliSecond_ = 0;

}

DinamicScaleCalculation::~DinamicScaleCalculation(){


}

void DinamicScaleCalculation::Initialize(){

	if (this->scalePoints_.size() != 0){
		this->nowPoint_ = this->scalePoints_.begin();
	}

	this->totalElapsedMilliSecond_ = 0;

}

Vector3 DinamicScaleCalculation::UpdateScale(int elapsedMilliSecond){

	if (this->scalePoints_.size() == 0) {

		return Vector3_One;
	
	}

	if (this->nowPoint_ == this->scalePoints_.end()) {

		ScalePoint scalePoint = *(this->nowPoint_ - 1);
		return scalePoint.scale;

	}

	ScalePoint nowScalePoint = *(this->nowPoint_);
	
	this->totalElapsedMilliSecond_ = elapsedMilliSecond;
	if (this->totalElapsedMilliSecond_ >= nowScalePoint.delayMilliSecond){

		this->totalElapsedMilliSecond_ -= nowScalePoint.delayMilliSecond;

		this->nowPoint_++;
		if (this->nowPoint_ == this->scalePoints_.end()){

			return nowScalePoint.scale;

		}

		nowScalePoint = *(this->nowPoint_);

	}
	
	ScalePoint prevScalePoint = ScalePoint(0, this->START_SCALE_);
	if (this->nowPoint_ != this->scalePoints_.begin()){

		prevScalePoint = *(this->nowPoint_ - 1);

	}

	Vector3 dirScale			= nowScalePoint.scale - prevScalePoint.scale;
	int		dirDelayMilliSecond = nowScalePoint.delayMilliSecond;
	
	float	timeRate  = (float)this->totalElapsedMilliSecond_ / (float)dirDelayMilliSecond;
	Vector3 baseScale = prevScalePoint.scale;

	return baseScale + (dirScale * timeRate);

}

void DinamicScaleCalculation::AddScalePoint(int milliSecond, Vector3 scale){

	ScalePoint scalePoint;
	scalePoint.milliSecond = milliSecond;
	scalePoint.scale = scale;

	//Q.AddNoteAlgorithm使わないの？
	//A.あれノート用

	if (this->scalePoints_.size() == 0){

		//１つもないなら入れる
		this->scalePoints_.push_back(scalePoint);

	}

	auto itr = this->scalePoints_.begin();

	while (itr != this->scalePoints_.end()){

		if (milliSecond <= itr->milliSecond){
			this->scalePoints_.insert(itr,scalePoint);
			return;
		}

	}

	//ここまで来たということは一番遅い
	this->scalePoints_.push_back(scalePoint);

}

bool DinamicScaleCalculation::HasAddScalePoint(int milliSecond, Vector3 scale){

	ScalePoint scalePoint;
	scalePoint.milliSecond = milliSecond;
	scalePoint.scale = scale;

	auto itr = std::find(this->scalePoints_.begin(),this->scalePoints_.end(),scalePoint);

	return (itr != this->scalePoints_.end());

}

void DinamicScaleCalculation::RemoveScalePoint(int milliSecond, Vector3 scale){

	ScalePoint scalePoint;
	scalePoint.milliSecond = milliSecond;
	scalePoint.scale = scale;

	//まず消そうとしているのがあるかどうか
	auto deleteItr = std::find(this->scalePoints_.begin(), this->scalePoints_.end(), scalePoint);

	if (deleteItr == this->scalePoints_.end()){

		return;
	
	}

	//要素除去によってイテレーターが変わるので元データを保持
	ScalePoint nowPointValue = *this->nowPoint_;

	this->scalePoints_.erase(deleteItr);

	//取っておいたデータを探してポインタ再取得
	this->nowPoint_ = std::find(this->scalePoints_.begin(), this->scalePoints_.end(), nowPointValue);

}