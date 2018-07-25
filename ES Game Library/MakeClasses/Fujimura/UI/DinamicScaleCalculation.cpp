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

	auto backItr = this->scalePoints_.end();
	backItr--;

	if (this->nowPoint_ == backItr) {

		ScalePoint scalePoint = *(this->nowPoint_);
		return scalePoint.scale;

	}

	ScalePoint nowScalePoint  = *(this->nowPoint_);
	ScalePoint nextScalePoint = *(this->nowPoint_ + 1);

	this->totalElapsedMilliSecond_ += elapsedMilliSecond;
	if (this->totalElapsedMilliSecond_ >= nextScalePoint.milliSecond){

		this->nowPoint_++;
		if (this->nowPoint_ == backItr){

			return nextScalePoint.scale;

		}

		nowScalePoint  = *(this->nowPoint_);
		nextScalePoint = *(this->nowPoint_ + 1);

	}

	Vector3 dirScale	   = nextScalePoint.scale		- nowScalePoint.scale;
	int		dirMilliSecond = nextScalePoint.milliSecond - nowScalePoint.milliSecond;

	float	timeRate  = (float)(this->totalElapsedMilliSecond_ - nowScalePoint.milliSecond) / (float)dirMilliSecond;
	Vector3 baseScale = nowScalePoint.scale;

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
		return;

	}

	auto itr = this->scalePoints_.begin();

	while (itr != this->scalePoints_.end()){

		if (milliSecond <= itr->milliSecond){
			this->scalePoints_.insert(itr,scalePoint);
			return;
		}

		itr++;

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