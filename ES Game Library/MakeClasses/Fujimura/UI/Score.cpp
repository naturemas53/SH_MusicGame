#include "Score.h"
#include "../../yoshi/effect/Effect_Singleton.h"

Score::Score(float scale) :
SCALE_(scale),
NUMBERSIZE_(Vector2(48.0f * scale, 67.0f * scale))
{

	this->noteCount_ = 1;
	
	this->numberSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/score_number.png"));
	this->textSp_ = GraphicsDevice.CreateSpriteFromFile(_T("NumberTexts/score_text.png"));
	this->offScreen_ = GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);

	this->score_ = 0;

}

Score::~Score(){

	GraphicsDevice.ReleaseRenderTarget(this->offScreen_);

}

void Score::Update(){



}

void Score::Draw(){

	GraphicsDevice.SetRenderTarget(this->offScreen_);
	GraphicsDevice.Clear(Color(0,0,0,0));

	SpriteBatch.Begin();

	float numberWidth = this->NUMBERSIZE_.x * 6.0f;
	float textWidth = 199.0f * this->SCALE_;

	float space = 1280.0f - (numberWidth + textWidth + 20.0f);
	Vector3 basePos = Vector3(space / 2.0f, 720.0f - this->NUMBERSIZE_.y - 5.0f, 0.0f);

	SpriteBatch.Draw(*this->textSp_, basePos, 1.0f, Vector3_Zero, Vector3_Zero, this->SCALE_);

	basePos.x += 20.0f + textWidth;
	int j = 0;
	for (int i = 100000; i > 0 ;i /= 10){
		{
			Vector3 drawPos = basePos;
			drawPos.x += j * this->NUMBERSIZE_.x;
			int number = (this->score_ / i) % 10;
			this->NumberDraw(drawPos,number);
			j++;

		}
	}

	SpriteBatch.End();

	GraphicsDevice.SetDefaultRenderTarget();

	SpriteBatch.Begin();

	SpriteBatch.InitTransform();
	SpriteBatch.DrawSimple(*this->offScreen_,Vector3_Zero);

	SpriteBatch.End();


}

void Score::NoticeJudge(JUDGE judge){

	this->counter_ = this->counter_ + judge;

	float rate = (float)this->counter_.GetScoreValue() / ((float) (this->noteCount_ * 100.0f));
	this->score_ = (int)(rate * 100000.0f);
}

void Score::NumberDraw(Vector3 pos, int number){

	Rect useRect = RectWH(number * 48,0,48,67);
	SpriteBatch.Draw(*this->numberSp_,pos,useRect,1.0f,Vector3_Zero,Vector3_Zero,this->SCALE_);

}

void Score::SetNoteCount(int noteCount){
	this->noteCount_ = noteCount;
}