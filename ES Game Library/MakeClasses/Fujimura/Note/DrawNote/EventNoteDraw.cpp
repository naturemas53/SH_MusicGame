#include "EventNoteDraw.h"
#include "../../DataSingleton.h"
#include "../Note/Note.h"
#include "../../Lane/EventLane.h"
#include <typeinfo>

EventNoteDraw::EventNoteDraw(){


}

EventNoteDraw::~EventNoteDraw(){


}

void EventNoteDraw::NoteDraw(Note* note, BaseLane* lane, DWORD nowTime, DWORD drawRangeTime){

	if (typeid(*lane) != typeid(EventLane)) return;

	if (note->GetType() != Note::EVENTNOTE) return;
	SPRITE sp = Data.heartSp_;

	note->Draw(sp, Vector3_Zero);

}