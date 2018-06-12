#pragma once
#include "../../../ESGLib.h"
#include <vector>

class Note;
class MusicScoreIO;

class NoteManager{

public:

	NoteManager(MusicScoreIO* io);
	~NoteManager();

	void Update(DWORD nowtime);
	void Draw(DWORD nowtime);

	void EntryUI();

private:

	std::vector<Note*> notes_;

	//UIのポインタ
	//審判系のやつ配列３つ　ストラテジ　judgment
	//オブザなやつの配列


};