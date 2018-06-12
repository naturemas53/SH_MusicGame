#include "MusicScoreIO.h"
#include "Note\Factory\SingleNoteFactory.h"

MusicScoreIO::MusicScoreIO(std::string path) : PATH_(path){

	this->noteFactorys_['S'] = new SingleNoteFactory();
	//this->noteFactorys_['L'] = new LongNoteFactory();
	//this->noteFactorys_['H'] = new HeartNoteFactory();

}

MusicScoreIO::~MusicScoreIO(){

	for (auto data : this->noteFactorys_) delete data.second;

}

bool MusicScoreIO::ImportScore(std::vector<std::function<void(Note*)> >& writeData){

	FILE* musicScoreFile;
	char readBufferData[256] = {};

	musicScoreFile = fopen(this->PATH_.c_str(), "r");

	if (musicScoreFile == NULL) return false;
	//������BPM
	//do{
	//	if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
	//		return false; 
	//	}
	//} while (strncmp(readBufferData,"BPM",3) == 0);

	//�ł�����Score
	do{
		if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
			return false;
		}
	} while (strncmp(readBufferData, "NOTES", 5) == 0);

	//��������ǂݎ��
	{
		int laneNumber = 0;
		LONG timing = 0;
		//�O�v���O�����̖��c�@����̃v���W�F�N�g�ł͂���Ȃ�����
		//���ʊ����܂ŗ]�v�ɂ�����
		float dammy = 0;
		char type = 0;
		Note* note = 0;

		while (fscanf(musicScoreFile, "%d %ld %f %c", &laneNumber, &timing, &dammy, &type) != EOF){
			//�{���͒������悭�Ȃ��񂾂��ǁ@����Ȃ̂�
			//���[����2�����Ȃ��̂ŁA�����葽�������Ȃ玟�̃m�[�g��
			if (laneNumber > 1) continue;

			note = this->noteFactorys_[type]->Create(musicScoreFile, laneNumber, timing);
			if (note == nullptr) {
				fclose(musicScoreFile);
				return false;
			}

			//�m�[�g�ǉ�
			writeData[laneNumber](note);

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