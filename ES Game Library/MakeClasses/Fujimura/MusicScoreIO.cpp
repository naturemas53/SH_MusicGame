#include "MusicScoreIO.h"
#include "Note\Factory\SingleNoteFactory.h"
#include "Note\Factory\LongNoteFactory.h"
#include "Note\Factory\EventNoteFactory.h"
#include "Lane\Lane.h"
#include "Lane\EventLane.h"
#include "ArrayAlgorithm\AddNoteAlgorithm.h"

MusicScoreIO::MusicScoreIO(std::string path) : PATH_(path){

	this->noteFactorys_['S'] = new SingleNoteFactory();
	this->noteFactorys_['L'] = new LongNoteFactory();
	this->noteFactorys_['H'] = new EventNoteFactory();

}

MusicScoreIO::~MusicScoreIO(){

	for (auto data : this->noteFactorys_) delete data.second;

}

bool MusicScoreIO::ImportScore(std::vector<Lane*>& writeLane,EventLane* eventLane){

	FILE* musicScoreFile;
	char readBufferData[256] = {};

	musicScoreFile = fopen(this->PATH_.c_str(), "r");

	if (musicScoreFile == NULL) return false;

	//������Score
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

		BaseLane::VISITORMETHOD visitor = [&](BaseLane* lane){

			AddNoteAlgorithm().Execution(lane->GetNoteList(),note);
		
		};

		while (fscanf(musicScoreFile, "%d %d %f %c", &laneNumber, &timing, &dammy, &type) != EOF){
			
			//�ԍ������������傫�������玟��
			if (laneNumber >= writeLane.size()) continue;
			//�e�X�g�Ȃ�
			if (this->noteFactorys_.find(type) == this->noteFactorys_.end()) continue;

			note = this->noteFactorys_[type]->Create(musicScoreFile, laneNumber, timing);
			if (note == nullptr) {
				fclose(musicScoreFile);
				return false;
			}

			switch (type){

			case 'H':
				eventLane->Accept(visitor);
				break;

			default:
				writeLane[laneNumber]->Accept(visitor);
				break;
			}

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