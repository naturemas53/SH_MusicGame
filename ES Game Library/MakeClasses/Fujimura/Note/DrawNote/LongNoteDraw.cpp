#include "LongNoteDraw.h"
#include "SingleNoteDraw.h"
#include "../Note/LongNote.h"
#include "../../Lane/Lane.h"
#include "../../DataSingleton.h"

LongNoteDraw::LongNoteDraw(){


}

LongNoteDraw::~LongNoteDraw(){



}

void NoteDraw(Note* note, Lane* lane, DWORD nowTime, DWORD drawRangeTime){

	if (note->GetType() != Note::LONGNOTE) return;
	LongNote* longNote = (LongNote*)note;

	Vector3 startPos,hitPos;
	lane->GetLaneVectol(startPos,hitPos);
	Vector3 dir = hitPos - startPos;

	Vector3 baseNotePoint = Vector3_Zero;
	baseNotePoint.x -= note->GetSize().x / 2.0f;
	//後ろの帯表示
	
	baseNotePoint.y -= note->GetSize().y / 2.0f;
	Vector3 notePos;
	SPRITE sp = Data.atlasSp_;

	//ノートの下表示
	long dirTime = longNote->GetTiming() - (long)nowTime;
	float timeRate = (float)dirTime / (float)drawRangeTime;

	notePos = baseNotePoint + startPos + dir * timeRate;

	if (longNote->IsPushed()) notePos = baseNotePoint + hitPos;

	note->Draw(sp,notePos);

	//ノートの上を表示
	dirTime = longNote->GetEndTiming() - longNote->GetTiming();
	if (longNote->IsPushed()){
		dirTime = longNote->GetEndTiming() - nowTime;
	}

	timeRate = (float)dirTime / (float)drawRangeTime;
	notePos = baseNotePoint + hitPos + dir * -timeRate;

	note->Draw(sp, notePos);

}