#include "MusicScoreIO.h"
#include "Note\Factory\SingleNoteFactory.h"
#include "Lane\Lane.h"

MusicScoreIO::MusicScoreIO(std::string path) : PATH_(path){

	this->noteFactorys_['S'] = new SingleNoteFactory();
	//this->noteFactorys_['L'] = new LongNoteFactory();
	//this->noteFactorys_['H'] = new HeartNoteFactory();

}

MusicScoreIO::~MusicScoreIO(){

	for (auto data : this->noteFactorys_) delete data.second;

}

bool MusicScoreIO::ImportScore(std::vector<Lane*>& writeLane){

	FILE* musicScoreFile;
	char readBufferData[256] = {};

	musicScoreFile = fopen(this->PATH_.c_str(), "r");

	if (musicScoreFile == NULL) return false;

	//�ł�����Score
	do{
		if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
			return false;
		}
	} while (strncmp(readBufferData, "NOTES", 5) != 0);

	//��������ǂݎ��
	{
		int laneNumber = 0;
		LONG timing = 0;
		//�O�v���O�����̖��c�@����̃v���W�F�N�g�ł͂���Ȃ�����
		//���ʊ����܂ŗ]�v�ɂ�����
		float dammy = 0;
		char type = 0;
		Note* note = 0;

		while (fscanf(musicScoreFile, "%d %d %f %c", &laneNumber, &timing, &dammy, &type) != EOF){
			
			//�ԍ������������傫�������玟��
			if (laneNumber >= writeLane.size()) continue;
			//�e�X�g�Ȃ�
			if (this->noteFactorys_.find(type) == this->noteFactorys_.end()) continue;

			if (timing == 47343){

				int a = 1919191919419;

			}

			note = this->noteFactorys_[type]->Create(musicScoreFile, laneNumber, timing);
			if (note == nullptr) {
				fclose(musicScoreFile);
				return false;
			}

			//�m�[�g�ǉ�
			writeLane[laneNumber]->AddNote(note);

		}
	}

	fclose(musicScoreFile);
	return true;

}

bool MusicScoreIO::ImportBPM(std::vector<BpmData>& writeData){

	FILE* musicScoreFile;
	char readBufferData[256] = {};

	//�ǂݎ���p�œǂނ���
	musicScoreFile = fopen(this->PATH_.c_str(), "r");

	if (musicScoreFile == NULL) return false;

	do{
		if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
			return false; 
		}
	} while (strncmp(readBufferData,"BPM",3) == 0);

	return true;
}