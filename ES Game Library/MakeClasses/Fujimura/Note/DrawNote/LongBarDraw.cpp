#include "LongBarDraw.h"
#include "../Note/LongNote.h"
#include "../../DataSingleton.h"
#include <math.h>

LongBarDraw::LongBarDraw(){

}

LongBarDraw::~LongBarDraw(){

}

void LongBarDraw::BarDraw(Vector3 startPos, Vector3 endPos, LongNote* note){

	Vector3 barDir = endPos - startPos;

	//Šp“xŒvŽZ
	float angle = MathHelper_Atan2(barDir.y,barDir.x);
	if (barDir.x == 0.0f || barDir.y == 0.0f) angle = 0.0f;

	//hypotenuse = ŽÎ•Ó@ƒo[‚Ì’·‚³‚ðŒvŽZ
	barDir.x *= barDir.x;
	barDir.y *= barDir.y;
	float hypotenuse = barDir.x + barDir.y;
	hypotenuse = sqrtf(hypotenuse);

	SPRITE sp = Data.longSquareSp_;

	note->DrawBar(sp,startPos,angle,hypotenuse);

}