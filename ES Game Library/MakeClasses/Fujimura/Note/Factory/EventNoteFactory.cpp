#include "EventNoteFactory.h"
#include "../Note/EventNote.h"

EventNoteFactory::EventNoteFactory(){


}

EventNoteFactory::~EventNoteFactory(){


}

Note* EventNoteFactory::FactoryMethod(FILE* fp, int laneNumber, LONG timing){

	return new EventNote(timing);

}