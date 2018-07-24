#include "IntValueSimpleDraw.h"

void IntValueSimpleDraw::Draw(SPRITE sprite, Vector3 drawPos,Color color, Vector2 imageOneCellSize){

	int i = 1;
	int j = 0;

	Vector3 basePos = drawPos;

	Vector2 scale = this->DRAW_ONE_CELL_SIZE_;
	scale.x /= imageOneCellSize.x;
	scale.y /= imageOneCellSize.y;
	if (scale == Vector2_Zero){
		scale = Vector2_One;
	}

	for (; i <= this->value_; i *= 10);

	//上の配列終わった時点では
	// value = 12345  i = 100000
	//みたいに1桁飛び出しているので、
	// /10で1桁もどす
	//　ただ、１なら何もしない
	if (i > 1)
	{
		i /= 10;
	}

	for (; i >= 1;i /= 10){
		{
			Vector3 revisionDrawPos = basePos;
			revisionDrawPos.x += j * imageOneCellSize.x * scale.x;
			int number = (this->value_ / i) % 10;
			Rect rect = RectWH(imageOneCellSize.x * number, 0, imageOneCellSize.x, imageOneCellSize.y);
			SpriteBatch.Draw(*sprite, revisionDrawPos, rect, color, Vector3_Zero, Vector3_Zero, scale);
			j++;
		}

	}

}