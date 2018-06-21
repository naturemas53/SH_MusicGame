#include "DeleteNoteAlgorithm.h"
#include "../Note/Note/Note.h"

void DeleteNoteAlgorithm::Execution(std::vector<Note*>& notes, Note* note){

	auto itr = std::find(notes.begin(),notes.end(),note);
	if (itr != notes.end()){
		delete note;
	}

}