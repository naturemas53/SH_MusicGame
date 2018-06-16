#include "SingleNoteDraw.h"
#include "../Note/Note.h"
#include "../../Lane/Lane.h"
#include "../../DataSingleton.h"

SingleNoteDraw::SingleNoteDraw(){


}

SingleNoteDraw::~SingleNoteDraw(){


}

void SingleNoteDraw::NoteDraw(Note* note, Lane* lane, float timeRate){

	Vector3 startPos;
	Vector3 hitPos;
	lane->GetLaneVectol(startPos,hitPos);

	Vector3 dir = hitPos - startPos;
	Vector3 drawPos = startPos + dir * timeRate;
	
	Vector2 noteSize = note->GetSize();
	drawPos.x -= noteSize.x / 2.0f;
	drawPos.y -= noteSize.y / 2.0f;

	SPRITE sp = Data.atlasSp_;

	note->Draw(sp,drawPos);

}