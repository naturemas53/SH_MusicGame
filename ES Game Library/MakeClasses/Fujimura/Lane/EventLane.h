#pragma once
#include <d3dx9.h>
#include <vector>
#include <functional>
#include "BaseLane.h"

class JudgementContext;
class JudgeBomb;

class EventLane : public BaseLane{

public:


	EventLane(JudgementContext* judgment);
	~EventLane();

	void Update(DWORD nowTime);
	void Draw(DWORD nowTime);

	void Accept(VISITORMETHOD visitorMethod);
	//void EntryPostMethod();

private:

	JudgementContext* judgement_;
	JudgeBomb* bomb_;

};