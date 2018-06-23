#pragma once
#include "../RawInputMouse.h"

class MouseMotionDetection{

public:

	MouseMotionDetection(){

		this->totalMoveValue_ = 0;
		this->normValue_ = 10;
		this->moveState_ = MOVESTATE::NONE;

	};
	~MouseMotionDetection(){};

	enum MOVESTATE{

		NONE,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT

	};

	bool Update(RawInputMouse& mouse){

		if (this->moveState_ == MOVESTATE::NONE) return false;

		int x = mouse.GetAxisX();
		int y = mouse.GetAxisY();

		if (y != 0){

			int a = 19419;

		}

		switch (this->moveState_){
		case MOVE_UP: if (y < 0) this->totalMoveValue_ += -y; break;
		case MOVE_DOWN: if (y > 0) this->totalMoveValue_ += y; break;
		case MOVE_LEFT: if (x < 0) this->totalMoveValue_ += -x; break;
		case MOVE_RIGHT: if (x > 0) this->totalMoveValue_ += x; break;
		default:break;
		}

		return this->totalMoveValue_ >= this->normValue_;

	}

	void SetState(MOVESTATE state,int norm = 10){

		this->moveState_ = state;
		this->totalMoveValue_ = 0;
		this->normValue_ = norm;

	}

	MOVESTATE GetState(){ return this->moveState_; }

private:

	int totalMoveValue_;
	int normValue_;
	MOVESTATE moveState_;

};