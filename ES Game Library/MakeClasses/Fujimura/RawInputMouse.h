#pragma once
#include "../../Extension/MultiDevice/RawInputListeners.h"
#include "../../Extension/MultiDevice/RawInput.h"
#include <map>

enum MOUSEBUTTON{

	LEFTBUTTON = 0,
	RIGHTBUTTON = 1

};

class RawInputMouse{

public:
	explicit RawInputMouse(RawInputReceiver& reciver, int inNum);
	~RawInputMouse();

	void Update();

	int GetAxisX();
	int GetAxisY();
	int GetWheelValue();
	bool IsButtonDown(MOUSEBUTTON button);
	bool IsButtonUp(MOUSEBUTTON button);
	bool IsPushed(MOUSEBUTTON button);
	bool IsReleased(MOUSEBUTTON button);

private:

	RiMouseState rawInput;
	std::map<MOUSEBUTTON, bool> prevPushFlags_;

};