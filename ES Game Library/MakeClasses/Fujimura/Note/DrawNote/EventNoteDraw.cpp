#include "EventNoteDraw.h"
#include "../../DataSingleton.h"
#include "../Note/Note.h"
#include "../../Lane/EventLane.h"
#include <typeinfo>

EventNoteDraw::EventNoteDraw(){


}

EventNoteDraw::~EventNoteDraw(){


}

void EventNoteDraw::NoteDraw(Note* note, BaseLane* lane, LONG nowTime, LONG drawRangeTime){

	if (typeid(*lane) != typeid(EventLane)) return;
	if (note->GetType() != Note::EVENTNOTE) return;
	long dirTime = note->GetTiming() - nowTime;

	SPRITE sp = Data.heartSp_;

	float width = 867.0f;
	float height = 753.0f;

	width = 1280.0f - width;
	height = 720.0f - height - 120.0f;

	note->Draw(sp, Vector3(width / 2.0f,height / 2.0f,0.0f));

}