#include "LongNoteDraw.h"
#include "SingleNoteDraw.h"
#include "LongBarDraw.h"
#include "../Note/LongNote.h"
#include "../../Lane/Lane.h"
#include "../../DataSingleton.h"

LongNoteDraw::LongNoteDraw(){


}

LongNoteDraw::~LongNoteDraw(){



}

void LongNoteDraw::NoteDraw(Note* note, Lane* lane, DWORD nowTime, DWORD drawRangeTime){

	if (note->GetType() != Note::LONGNOTE) return;
	LongNote* longNote = (LongNote*)note;

	Vector3 startPos, hitPos;
	lane->GetLaneVectol(startPos, hitPos);
	Vector3 dir = hitPos - startPos;

	Vector3 baseNotePoint = Vector3_Zero;
	baseNotePoint.x -= note->GetSize().x / 2.0f;
	baseNotePoint.y -= note->GetSize().y / 2.0f;

	Vector3 startNotePos,endNotePos;
	SPRITE sp = Data.atlasSp_;

	//ノートの始点を計算
	long dirTime = longNote->GetTiming() - (long)nowTime;
	long progressTime = drawRangeTime - dirTime;
	float timeRate = (float)progressTime / (float)drawRangeTime;

	startNotePos = baseNotePoint + startPos + dir * timeRate;

	if (longNote->IsPushed()){
		startNotePos = baseNotePoint + hitPos;
	}


	//ノートの終点を計算
	dirTime = longNote->GetEndTiming() - longNote->GetTiming();
	if (longNote->IsPushed()){
		dirTime = longNote->GetEndTiming() - nowTime;
	}

	timeRate = (float)dirTime / (float)drawRangeTime;
	endNotePos = startNotePos + (dir * -timeRate);

	LongBarDraw().BarDraw(startNotePos,endNotePos,longNote);
	note->Draw(sp, startNotePos);
	note->Draw(sp, endNotePos);

}