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

		//�Ԃ茌��NONE�łȂ���Βʒm���폜

}

void NoteManager::Draw(DWORD nowtime){

	for (auto note : this->notes_){

		//note->Draw(sp,pos);

	}

}