#include "NoteManager.h"
#include "../MusicScoreIO.h"

NoteManager::NoteManager(MusicScoreIO* io){

	io->ImportScore(this->notes_);

}

NoteManager::~NoteManager(){

	for (auto note : this->notes_) delete note;

}

void NoteManager::Update(DWORD nowtime){

	auto itr = this->notes_.begin();

		//•Ô‚èŒŒ‚ªNONE‚Å‚È‚¯‚ê‚Î’Ê’mŒ“íœ

}

void NoteManager::Draw(DWORD nowtime){

	for (auto note : this->notes_){

		//note->Draw(sp,pos);

	}

}