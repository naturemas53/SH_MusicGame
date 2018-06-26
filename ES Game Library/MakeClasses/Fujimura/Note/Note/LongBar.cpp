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
	Color color = Color(255, 255, blue, 128);

	drawPos.y -= noteSize.y + 5.0f;

	float spWidth = sp->GetWidth();
	float spHeight = 73.0f;

	Vector2 scale = Vector2_Zero;
	scale.x = noteSize.x / spWidth;
	scale.y = noteSize.y / spHeight;
	scale.y *= hypotenuse / noteSize.y;

	SpriteBatch.Draw(*sp, drawPos, color,
		Vector3(0.0f, 0.0f, angle),
		Vector3(spWidth / 2.0f, spHeight, 0.0f),
		scale);

}