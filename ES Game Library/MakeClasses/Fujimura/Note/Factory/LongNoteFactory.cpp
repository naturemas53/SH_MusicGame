#include "LongNoteFactory.h"
#include "../Note/LongNote.h"

LongNoteFactory::LongNoteFactory(){}
LongNoteFactory::~LongNoteFactory(){}

Note* LongNoteFactory::FactoryMethod(FILE* fp, int laneNumber, LONG timing){

	LongNote* note = new LongNote(timing);

	//�O�v���O�����̖��c�@����̃v���W�F�N�g�ł͂���Ȃ�����
	//���ʊ����܂ŗ]�v�ɂ�����
	float dammy = 0;
	char type = 0;
	fscanf(fp, "%d %d %f %c", &laneNumber, &timing, &dammy, &type);

	note->SetEndTiming(timing);

	return note;

}