#include "SingleNoteDraw.h"
#include "../Note/Note.h"
#include "../../Lane/Lane.h"
#include "../../DataSingleton.h"
#include <typeinfo>

SingleNoteDraw::SingleNoteDraw(){


}

SingleNoteDraw::~SingleNoteDraw(){


}

void SingleNoteDraw::NoteDraw(Note* note, BaseLane* lane, LONG nowTime, LONG drawRangeTime){

	if (typeid(*lane) != typeid(Lane)) return;

	Lane* normalLane = (Lane*)lane;

	if (note->GetType() != Note::SINGLENOTE) return;

	long dirTime = note->GetTiming() - (long)nowTime;

	long progressTime = (long)drawRangeTime - dirTime;
	float timeRate = (float)progressTime / (float)drawRangeTime;

	Vector3 startPos, hitPos;
	normalLane->GetLaneVectol(startPos, hitPos);

	Vector3 dir = hitPos - startPos;
	Vector3 drawPos = startPos + dir * timeRate;
	
	Vector2 noteSize = note->GetSize();
	drawPos.x -= noteSize.x / 2.0f;
	drawPos.y -= noteSize.y / 2.0f;

	SPRITE sp = Data.normalNoteSp_;

	note->Draw(sp,drawPos);

}