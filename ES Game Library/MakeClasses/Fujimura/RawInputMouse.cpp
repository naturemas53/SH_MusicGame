#include "RawInputMouse.h"

/**
* @file RawInputMouse.cpp
* @brief RawInputの海外サンプルを使いやすいよう改良
* @author So Fujimura
* @date 2018/06/05
*/
RawInputMouse::RawInputMouse(RawInputReceiver& reciver, HRIDEV inHundle){

	reciver.addMouseListener(inHundle,&(this->rawInput));
	this->prevPushFlags_[LEFTBUTTON] = false;
	this->prevPushFlags_[RIGHTBUTTON] = false;

}

RawInputMouse::~RawInputMouse(){


}

void RawInputMouse::Update(){

	auto itr = this->prevPushFlags_.begin();
	for (int i = 0; i < this->prevPushFlags_.size();i++){

		{
			(*itr).second = this->rawInput.button((*itr).first);
			itr++;
		}

	}

	this->rawInput.reset();

}

int RawInputMouse::GetAxisX(){ return this->rawInput.diffX(); }
int RawInputMouse::GetAxisY(){ return this->rawInput.diffY(); }
int RawInputMouse::GetWheelValue(){ return this->rawInput.diffW(); }

bool RawInputMouse::IsButtonDown(MOUSEBUTTON button){ return this->rawInput.button(button); }
bool RawInputMouse::IsButtonUp(MOUSEBUTTON button){ return !(this->rawInput.button(button)); }

bool RawInputMouse::IsPushed(MOUSEBUTTON button){

	if (!(this->IsButtonDown(button))) return false;
	return this->prevPushFlags_[button] != this->IsButtonDown(button);

}

bool RawInputMouse::IsReleased(MOUSEBUTTON button){

	if (!(this->IsButtonUp(button))) return false;
	return this->prevPushFlags_[button] != this->IsButtonUp(button);

}