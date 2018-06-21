#pragma once
#include <d3dx9.h>
#include <vector>
#include <functional>
#include "BaseLane.h"

class EventLane : public BaseLane{

public:

	EventLane();
	~EventLane();

	void Update(DWORD nowTime);
	void Draw(DWORD nowTime);

	void Accept(VISITORMETHOD visitorMethod);

private:


};