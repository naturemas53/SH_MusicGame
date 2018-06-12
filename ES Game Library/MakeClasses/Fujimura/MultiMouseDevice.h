#pragma once
#include "../../ESGLib.h"
#include "../../Extension/MultiDevice/RawInputListeners.h"
#include "RawInputMouse.h"

class MultiMouseDevice{

public:

	~MultiMouseDevice(){};

	static MultiMouseDevice& GetInstance(){

		static MultiMouseDevice instance;
		return instance;
	
	}

	void StartListening();
	void Update();

	int GetDeviceCount();
	RiDetector<RiMouseListener>& GetDetector(){ return this->mouseDetector_; }
	RawInputMouse& GetInputData(int mouseNumber);

private:

	MultiMouseDevice(){
	
		this->listeningFlag_ = false;

	};
	
	bool listeningFlag_;
	std::vector<RawInputMouse> mouses_;
	RiDetector<RiMouseListener> mouseDetector_;

};

#define MultiMouse MultiMouseDevice::GetInstance()