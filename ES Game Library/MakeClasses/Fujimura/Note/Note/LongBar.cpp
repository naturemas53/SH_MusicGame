#include "LongBar.h"

LongBar::LongBar(): MAX_LIGHT_VALUE_(30)
{

	this->nowLightValue_ = 0;

}

LongBar::~LongBar(){

}

void LongBar::Update(){

	this->nowLightValue_++;

}

void LongBar::Draw(SPRITE sp, Vector3 drawPos, Vector2 noteSize, float angle, float hypotenuse){

	int lightCount;
	lightCount = this->nowLightValue_ % this->MAX_LIGHT_VALUE_;
	int val = this->nowLightValue_ / this->MAX_LIGHT_VALUE_;
	if (! (val % 2)){
		lightCount = this->MAX_LIGHT_VALUE_ - lightCount;
	}

	int blue = (int)(255.0f * ((float)lightCount / (float)this->MAX_LIGHT_VALUE_));
	Color color = Color(255, 255, blue, 255);

	Rect useRect = RectWH(64, 80 + 32, 64, 32);
	//ÇÌÇ©ÇÒÇ»Ç¢ÇÃÇ≈âûã}èàíu
	drawPos.y -= noteSize.y / 2.0f;

	SpriteBatch.Draw(*sp, drawPos, useRect, color,
		Vector3(0.0f, 0.0f, angle),
		Vector3(noteSize.x / 2.0f, noteSize.y, 0.0f),
		Vector2(1.0f, hypotenuse / noteSize.y));

}