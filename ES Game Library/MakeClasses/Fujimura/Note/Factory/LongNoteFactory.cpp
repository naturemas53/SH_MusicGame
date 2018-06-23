#include "LongNoteFactory.h"
#include "../Note/LongNote.h"

LongNoteFactory::LongNoteFactory(){}
LongNoteFactory::~LongNoteFactory(){}

Note* LongNoteFactory::FactoryMethod(FILE* fp, int laneNumber, LONG timing){

	LongNote* note = new LongNote(timing);

	//前プログラムの名残　今回のプロジェクトではいらないけど
	//譜面完成まで余計にもっ得
	float dammy = 0;
	char type = 0;
	fscanf(fp, "%d %d %f %c", &laneNumber, &timing, &dammy, &type);

	note->SetEndTiming(timing);

	return note;

}