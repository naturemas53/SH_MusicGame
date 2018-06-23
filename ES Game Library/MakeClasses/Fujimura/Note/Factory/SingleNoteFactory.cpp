#include "SingleNoteFactory.h"
#include "../Note/SingleNote.h"

Note* SingleNoteFactory::FactoryMethod(FILE* fp, int laneNumber, LONG timing){

	return new SingleNote(timing);

}