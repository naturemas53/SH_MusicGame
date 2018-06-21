#include "AddNoteAlgorithm.h"
#include "../Note/Note/Note.h"

void AddNoteAlgorithm::Execution(std::vector<Note*>& notes, Note* note){

	if (notes.size() == 0){
		notes.push_back(note);
		return;
	}

	int targetTiming = note->GetTiming();
	auto itr = notes.begin();

	while (itr != notes.end()){

		if (targetTiming < (*itr)->GetTiming()){
			notes.insert(itr,note);
			return;
		}

		itr++;

	}

	notes.push_back(note);

}