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

	//Q.AddNoteAlgorithm�g��Ȃ��́H
	//A.����m�[�g�p

	if (this->scalePoints_.size() == 0){

		//�P���Ȃ��Ȃ�����
		this->scalePoints_.push_back(scalePoint);

	}

	auto itr = this->scalePoints_.begin();

	while (itr != this->scalePoints_.end()){

		if (milliSecond <= itr->milliSecond){
			this->scalePoints_.insert(itr,scalePoint);
			return;
		}

	}

	//�����܂ŗ����Ƃ������Ƃ͈�Ԓx��
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

	//�܂��������Ƃ��Ă���̂����邩�ǂ���
	auto deleteItr = std::find(this->scalePoints_.begin(), this->scalePoints_.end(), scalePoint);

	if (deleteItr == this->scalePoints_.end()){

		return;
	
	}

	//�v�f�����ɂ���ăC�e���[�^�[���ς��̂Ō��f�[�^��ێ�
	ScalePoint nowPointValue = *this->nowPoint_;

	this->scalePoints_.erase(deleteItr);

	//����Ă������f�[�^��T���ă|�C���^�Ď擾
	this->nowPoint_ = std::find(this->scalePoints_.begin(), this->scalePoints_.end(), nowPointValue);

}