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
	SpriteBatch.Draw(*this->textSp_,Vector3_Zero,1.0f,Vector3_Zero,Vector3_Zero,this->SCALE_);

	int j = 0;
	for (int i = 100000; i > 0 ;i /= 10){
		{

			int number = (this->score_ / i) % 10;
			this->NumberDraw(Vector3(this->NUMBERSIZE_.x * j + (textWidth + 20.0f),0.0f,0.0f),number);
			j++;

		}
	}

	SpriteBatch.End();

	GraphicsDevice.SetDefaultRenderTarget();

	SpriteBatch.Begin();

	Vector3 drawPos = Vector3_Zero;
	drawPos.x = 1280.0f - (textWidth + numberWidth + 20.0f);
	drawPos.x /= 2.0f;
	drawPos.y = 720.0f - this->NUMBERSIZE_.y;

	SpriteBatch.Draw(*this->offScreen_, drawPos,
		 RectWH(0, 0, textWidth + numberWidth + 20,this->NUMBERSIZE_.y), Color(0,0,0));

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