#include "MusicScoreIO.h"
#include "Note\Factory\SingleNoteFactory.h"
#include "Note\Factory\LongNoteFactory.h"
#include "Note\Factory\EventNoteFactory.h"
#include "Lane\Lane.h"
#include "Lane\EventLane.h"
#include "ArrayAlgorithm\AddNoteAlgorithm.h"
#include <math.h>

MusicScoreIO::MusicScoreIO(std::string path) : PATH_(path.c_str()){

	this->noteFactorys_['S'] = new SingleNoteFactory();
	this->noteFactorys_['L'] = new LongNoteFactory();
	this->noteFactorys_['H'] = new EventNoteFactory();

}

MusicScoreIO::~MusicScoreIO(){

	for (auto data : this->noteFactorys_) delete data.second;

}

bool MusicScoreIO::ImportScore(std::vector<Lane*>& writeLane, EventLane* eventLane,int* noteCount){
	
	char readBufferData[256] = {};
	FILE* musicScoreFile = fopen(this->PATH_.c_str(), "r");

	if (musicScoreFile == NULL){
		return false;
	}

	//こいつがScore
	do{
		//読み終わりまでSCOREの文字が見つからなければ失敗とする
		if (fscanf(musicScoreFile, "%s", readBufferData) == EOF){
			return false;
		}
	} while (strncmp(readBufferData, "NOTES", 5) != 0);


	//ここから読み取り
	int laneNumber = 0;
	LONG timing = 0;
	//前プログラムの名残でいらないのがある
	//このdammyがそれ
	float dammy = 0;
	char type = 0;
	Note* note = nullptr;
	Note* prevNote = nullptr;

	BaseLane::VISITORMETHOD visitor = [&](BaseLane* lane){

		AddNoteAlgorithm().Execution(lane->GetNoteList(),note);
		
	};

	while (fscanf(musicScoreFile, "%d %d %f %c", &laneNumber, &timing, &dammy, &type) != EOF){
			
		prevNote = note;

		//番号が生成数より大きかったら次へ
		if (laneNumber >= writeLane.size()) continue;
		//生成しようとしているノートのファクトリーがあるかどうか
		if (this->noteFactorys_.find(type) == this->noteFactorys_.end()){
			continue;
		}
		note = this->noteFactorys_[type]->Create(musicScoreFile, laneNumber, timing);
		if (note == nullptr) {
			fclose(musicScoreFile);
			return false;
		}

		switch (type){
		case 'H': eventLane->Accept(visitor);			  break;
		default:  writeLane[laneNumber]->Accept(visitor); break;
		}

		if (noteCount != nullptr) {
			(*noteCount)++;
		}

		if (prevNote == nullptr){
			//最初の1つ目だけ同時押し比べるとかがないので
			continue;
		}

		//同時押し判定処理
		{
			int prevTiming =	prevNote->GetTiming();
			int currentTiming = note->GetTiming();

			//10msぐらい多分誤差
			if (labs(prevTiming - currentTiming) < 10){
				//同時押しだよと伝える
				prevNote->NoticeOtherTimingSame();
				note->	  NoticeOtherTimingSame();
			}
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