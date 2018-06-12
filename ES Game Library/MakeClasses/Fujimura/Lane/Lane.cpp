#include "Lane.h"
#include "../Note/Note/Note.h"

Lane::Lane(SPRITE sp,Vector3 inPos) : 
SIZE_(Vector2(512.0f,100.0f)),
POS_(inPos){

}

Lane::~Lane(){

	for (auto note : this->notes_) delete note;

}

void Lane::Draw(DWORD nowTime){

	//�e�X�g�R�[�h�}�[��
	Rect userect = RectWH(0, 0, 512, 100);

	SpriteBatch.Draw(*this->sp_,this->POS_);
	for (auto note : this->notes_) note->Draw(this->sp_,Vector3_Zero);

}

void Lane::AddNote(Note* note){

	//�������������ĂȂ��Ȃ����ďI���
	if (this->notes_.size() == 0){
		notes_.push_back(note);
		return;
	}

	int insertTiming = note->GetTiming();
	auto itr = this->notes_.begin();

	while (itr != this->notes_.end()){

		if (insertTiming < (*itr)->GetTiming()){

			this->notes_.insert(itr, note);
			return;

		}

		itr++;

	}

	//�����܂ŗ����Ƃ��͂P�Ԓx��
	notes_.push_back(note);

}

void Lane::EraseNote(Note* deletenote){

	auto itr = std::find(this->notes_.begin(), this->notes_.end(),deletenote);
	if (itr == this->notes_.end()) return;

	delete deletenote;
	this->notes_.erase(itr);

}