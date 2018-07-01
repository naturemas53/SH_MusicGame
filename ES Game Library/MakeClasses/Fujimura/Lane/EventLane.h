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

	void Update(LONG nowTime);
	void Draw(LONG nowTime);

	void Accept(VISITORMETHOD visitorMethod);
	void EntryPostMethod(std::function<void(VISITORMETHOD)> postMethod);

private:

	VISITORMETHOD drawJudgeVisitor_;
	std::function<void(VISITORMETHOD)> postMethod_;
	JudgementContext* judgement_;
	JudgeBomb* bomb_;

};