#include "EventLane.h"

EventLane::EventLane(){


}

EventLane::~EventLane(){


}

void EventLane::Update(DWORD nowTime){



}

void EventLane::Draw(DWORD nowTime){



}

void EventLane::Accept(VISITORMETHOD visit){

	visit(this);

}