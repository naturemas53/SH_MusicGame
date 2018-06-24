#include "DetectMultiMotion.h"

DetectMultiMotion::DetectMultiMotion(){

	this->mouseDetection_ = MouseMotionDetection();

}

DetectMultiMotion::~DetectMultiMotion(){


}

void DetectMultiMotion::Initialize(){

	this->nowNorm_ = this->normMoves_.begin();
	if (this->nowNorm_ == this->normMoves_.end()) return;
	MOVESET set = (*this->nowNorm_);
	this->mouseDetection_.SetState(set.first,set.second);

}

bool DetectMultiMotion::Update(RawInputMouse& mouse){

	bool completedFlag = this->mouseDetection_.Update(mouse);
	if (!completedFlag) return false;
	
	auto e_itr = this->normMoves_.end();
	e_itr--;

	if (this->nowNorm_ != e_itr){
		this->nowNorm_++;
		MOVESET set = (*this->nowNorm_);
		this->mouseDetection_.SetState(set.first, set.second);
		return false;
	}

	return true;

}

void DetectMultiMotion::AddNormSet(MOVESET addSet){

	this->normMoves_.push_back(addSet);

}