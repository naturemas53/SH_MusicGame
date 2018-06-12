#pragma once
#include <d3dx9.h>
#include <vector>

class Note;

//ŽÀŽ¿ƒŒ[ƒ“‚²‚Æ‚ÌNoteManagerŒN
class Lane{

public:

	Lane(SPRITE sp,Vector3 inPos);
	~Lane();

	void Draw(DWORD nowTime);

	void AddNote(Note* note);
	void EraseNote(Note* deleteitr);

	Note* GetTopNote(){ return (*this->notes_.begin()); }
	Vector2 GetSize(){ return this->SIZE_; }

private:

	const Vector2 SIZE_;
	const Vector3 POS_;

	SPRITE sp_;
	std::vector<Note*> notes_;

};