#include "Score.h"
#include "../../yoshi/effect/Effect_Singleton.h"

Score::Score(Vector3 drawPos, int noteCount, float scale) :
POS_(drawPos),
NUMBERSIZE_(Vector2(48.0f * scale,67.0f * scale))
{

	this->noteCount_ = noteCount;
	
	this->numberSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/score_number.png"));
	this->textSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/score_text.png"));

	this->score_ = 0;

}

Score::~Score(){

}

void Score::Update(){



}

void Score::Draw(){

	float numbersWidth = this->NUMBERSIZE_.x * 6.0f;

	SpriteBatch.Begin();

	SpriteBatch.End();

	for (int i = 100000;;i /= 10){
		{
			int number = (this->score_ / i) % 10;
			this->NumberDraw(Vector3_Zero,number);
		}
	}

}

void Score::NoticeJudge(JUDGE judge){

	this->counter_ = this->counter_ + judge;

	float rate = (float)this->counter_.GetScoreValue() / ((float) this->noteCount_);
	this->score_ = (int)(rate * 100000.0f);
}

void Score::NumberDraw(Vector3 pos, int number){

	Rect useRect = RectWH(number * 48,0,48,67);
	SpriteBatch.Draw(*this->numberSp_,pos,1.0f);

}