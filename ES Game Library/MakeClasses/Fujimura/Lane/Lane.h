#pragma once
#include <d3dx9.h>
#include <vector>

class Note;
class JudgeContext;

//ŽÀŽ¿ƒŒ[ƒ“‚²‚Æ‚ÌNoteManagerŒN
class Lane{

public:

	Lane(Vector3 inPos,JudgeContext* inJudge);
	~Lane();

	void Draw(DWORD nowTime);

	void AddNote(Note* note);
	void EraseNote(Note* deleteitr);

	Note* GetTopNote(){ return (*this->notes_.begin()); }
	Vector2 GetSize(){ return this->SIZE_; }

private:

	const Vector2 SIZE_;
	const Vector3 POS_;

	std::vector<Note*> notes_;
	JudgeContext* judge_;

};