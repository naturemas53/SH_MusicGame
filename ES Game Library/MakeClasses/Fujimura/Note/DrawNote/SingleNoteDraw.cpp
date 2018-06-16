#include "SingleNoteDraw.h"
#include "../Note/Note.h"
#include "../../Lane/Lane.h"
#include "../../DataSingleton.h"

SingleNoteDraw::SingleNoteDraw(){


}

SingleNoteDraw::~SingleNoteDraw(){


}

void SingleNoteDraw::NoteDraw(Note* note, Lane* lane,DWORD nowTime,DWORD drawRangeTime){

	long dirTime = note->GetTiming() - (long)nowTime;

	long progressTime = (long)drawRangeTime - dirTime;
	float timeRate = (float)progressTime / (float)drawRangeTime;

	Vector3 startPos, hitPos;
	lane->GetLaneVectol(startPos,hitPos);

	Vector3 dir = hitPos - startPos;
	Vector3 drawPos = startPos + dir * timeRate;
	
	Vector2 noteSize = note->GetSize();
	drawPos.x -= noteSize.x / 2.0f;
	drawPos.y -= noteSize.y / 2.0f;

	SPRITE sp = Data.atlasSp_;

	note->Draw(sp,drawPos);

}