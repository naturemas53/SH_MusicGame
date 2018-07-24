/**
* @file DetectMultiMotion.cpp
* @brief  マウスの一連の動きを検知するクラス 実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "DetectMultiMotion.h"

DetectMultiMotion::DetectMultiMotion(){

	this->mouseDetection_ = MouseMotionDetection();

}

DetectMultiMotion::~DetectMultiMotion(){


}

void DetectMultiMotion::Initialize(){

	//現在見てる判定の位置をはじめに
	this->nowNorm_ = this->normMoves_.begin();
	if (this->nowNorm_ == this->normMoves_.end()) return;
	MOVESET set = (*this->nowNorm_);
	this->mouseDetection_.SetState(set.first,set.second);

}

/**
* @brief マウスの一連の動きを感知する関数
* @param (mouse) 情報をもらうマウス
* @return bool 一連の動き全てを終えたかどうか
* @detail 直線の動きを順番に判定していき、
*		  全ての動きを終えた時にtrue、
*		  それ以外はfalseを返します。
*/
bool DetectMultiMotion::Update(RawInputMouse& mouse){

	bool completedFlag = this->mouseDetection_.Update(mouse);
	if (!completedFlag) return false;
	
	auto e_itr = this->normMoves_.end();
	e_itr--;

	//最後の動きでなければ
	if (this->nowNorm_ != e_itr){
		//次の動きをセットする
		this->nowNorm_++;
		MOVESET set = (*this->nowNorm_);
		this->mouseDetection_.SetState(set.first, set.second);
		return false;
	}

	//ここまで来たときはすべて終わらせた
	return true;

}

void DetectMultiMotion::AddNormSet(MOVESET addSet){

	this->normMoves_.push_back(addSet);

}