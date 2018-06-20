#pragma once
#include <d3dx9.h>
#include <vector>
#include "../../../ESGLib.h"

class Note;
class JudgeBomb;
class JudgementContext;

//�������[�����Ƃ�NoteManager�N
class Lane{

public:

	Lane(Vector3 inPos, JudgementContext* inJudge, int mouseNum);
	~Lane();

	void Update(DWORD nowTime);
	void Draw(DWORD nowTime);

	// ����Accepter (std::function<void (std::vector<Note*>) >)�@�ɂȂ�\��
	void AddNote(Note* note);
	void EraseNote(Note* deleteitr);

	Note* GetTopNote(){ return (*this->notes_.begin()); }
	Vector2 GetSize(){ return this->SIZE_; }
	void GetLaneVectol(Vector3 &startPos, Vector3 &hitPos);

private:

	const Vector2 SIZE_;
	const Vector3 POS_;


	int mouseNum_;

	std::vector<Note*> notes_;
	JudgementContext* judge_;
	JudgeBomb* bomb_;

};