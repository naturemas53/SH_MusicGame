#include "RawInputMouse.h"

RawInputMouse::RawInputMouse(RawInputReceiver& reciver, HRIDEV inHundle){

	reciver.addMouseListener(inHundle,&(this->rawInput));

}

RawInputMouse::~RawInputMouse(){


}

void RawInputMouse::Update(){

	for (auto flag : this->prevPushFlags_) flag.second = this->rawInput.button(flag.first);
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