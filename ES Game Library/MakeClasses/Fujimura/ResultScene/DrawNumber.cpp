#include "DrawNumber.h"

void DrawNumber::Draw(SPRITE sp, Vector3 pos, Vector2 oneCellSize, float scale, int value){

	int i = 1;
	int j = 0;
	Vector2 drawCellSize = oneCellSize * scale;
	Vector3 basePos = pos;

	for (; i <= value; i *= 10);

	//上の配列終わった時点では
	// value = 12345  i = 100000
	//みたいに1桁飛び出しているので、
	// /10で1桁もどす
	//　ただ、１なら何もしない
	if(i > 1)i /= 10;

	for (; i >= 1;i /= 10){
		{
			Vector3 drawPos = basePos;
			drawPos.x += j * drawCellSize.x;
			int number = (value / i) % 10;
			Rect rect = RectWH(oneCellSize.x * number, 0, oneCellSize.x, oneCellSize.y);
			SpriteBatch.Draw(*sp,drawPos,rect,1.0f,Vector3_Zero,Vector3_Zero,scale);
			j++;
		}

	}

}