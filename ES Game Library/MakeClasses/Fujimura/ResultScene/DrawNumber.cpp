#include "DrawNumber.h"

void DrawNumber::Draw(SPRITE sp, Vector3 pos, Vector2 oneCellSize, float scale, int value){

	int i = 1;
	int j = 0;
	Vector2 drawCellSize = oneCellSize * scale;
	Vector3 basePos = pos;

	for (; i <= value; i *= 10);

	//��̔z��I��������_�ł�
	// value = 12345  i = 100000
	//�݂�����1����яo���Ă���̂ŁA
	// /10��1�����ǂ�
	//�@�����A�P�Ȃ牽�����Ȃ�
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