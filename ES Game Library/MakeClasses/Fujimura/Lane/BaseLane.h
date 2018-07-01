#pragma once
#include <d3dx9.h>
#include <functional>
#include <vector>
#include "../Note/Note/Note.h"

class BaseLane{

public:

	BaseLane(){};
	~BaseLane(){

		for (auto note : this->notes_) delete note;

	}

	typedef std::function<void(BaseLane*)> VISITORMETHOD;

	virtual void Update(LONG nowTime) = 0;
	virtual void Draw(LONG nowTime) = 0;

	virtual void Accept(VISITORMETHOD visitorMethod) = 0;

	std::vector<Note*>& GetNoteList(){ return this->notes_; }

protected:

	std::vector<Note*> notes_;

};