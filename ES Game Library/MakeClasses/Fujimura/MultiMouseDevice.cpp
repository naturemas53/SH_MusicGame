#include "MultiMouseDevice.h"
#include "../../Framework/GameApp.hpp"

MultiMouseDevice::MultiMouseDevice(){

	this->listeningFlag_ = false;

};

MultiMouseDevice::~MultiMouseDevice(){
	for (auto mouse : this->mouses_) delete mouse;
}

void MultiMouseDevice::StartListening(){
	
	if (this->listeningFlag_) return;
	this->listeningFlag_ = true;

	RawInputReceiver& receiver = GameApp().GetReceiver();

	receiver.initDeviceStatus();

	for (int i = 0; i < this->GetDeviceCount();i++){

		this->mouses_.push_back(new RawInputMouse(receiver,this->mouseDetector_.getDeviceID(i)));

	}

}

void MultiMouseDevice::Update(){

	if (!(this->listeningFlag_)) return;
	for (auto mouse : this->mouses_) mouse->Update();

}

int MultiMouseDevice::GetDeviceCount(){ return this->mouseDetector_.getDeviceCount(); }

RawInputMouse& MultiMouseDevice::GetInputData(int mouseNumber){ 

	return *(this->mouses_[mouseNumber]); 

}