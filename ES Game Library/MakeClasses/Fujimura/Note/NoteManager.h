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

	//UI�̃|�C���^
	//�R���n�̂�z��R�@�X�g���e�W�@judgment
	//�I�u�U�Ȃ�̔z��


};