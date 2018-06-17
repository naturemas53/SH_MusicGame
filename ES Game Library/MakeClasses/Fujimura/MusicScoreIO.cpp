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

	//でこいつがScore
	do{
		if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
			return false;
		}
	} while (strncmp(readBufferData, "NOTES", 5) != 0);

	//ここから読み取り
	{
		int laneNumber = 0;
		LONG timing = 0;
		//前プログラムの名残　今回のプロジェクトではいらないけど
		//譜面完成まで余計にもっ得
		float dammy = 0;
		char type = 0;
		Note* note = 0;

		while (fscanf(musicScoreFile, "%d %d %f %c", &laneNumber, &timing, &dammy, &type) != EOF){
			
			//番号が生成数より大きかったら次へ
			if (laneNumber >= writeLane.size()) continue;
			//テストなう
			if (this->noteFactorys_.find(type) == this->noteFactorys_.end()) continue;

			if (timing == 47343){

				int a = 1919191919419;

			}

			note = this->noteFactorys_[type]->Create(musicScoreFile, laneNumber, timing);
			if (note == nullptr) {
				fclose(musicScoreFile);
				return false;
			}

			//ノート追加
			writeLane[laneNumber]->AddNote(note);

		}
	}

	fclose(musicScoreFile);
	return true;

}

bool MusicScoreIO::ImportBPM(std::vector<BpmData>& writeData){

	FILE* musicScoreFile;
	char readBufferData[256] = {};

	//読み取り専用で読むだけ
	musicScoreFile = fopen(this->PATH_.c_str(), "r");

	if (musicScoreFile == NULL) return false;

	do{
		if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
			return false; 
		}
	} while (strncmp(readBufferData,"BPM",3) == 0);

	return true;
}