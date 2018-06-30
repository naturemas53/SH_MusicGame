#include "HeartBeam.h"

HeartBeam::HeartBeam() : DRAW_RANGE_TIME_(1000){

	this->sp_ = GraphicsDevice.CreateSpriteFromFile(_T("heart_line.png"));
	this->pos_ = Vector3( (1280.0f - 426.0f) / 2.0f,(720.0f - 426.0f) / 2.0f - 60.0f,0.0f);

}

HeartBeam::~HeartBeam(){


}

void HeartBeam::Update(){

	if (this->heartsTimes_.size() <= 0) return;

	long elapsedTime = GameTimer.GetElapsedMilliSecond();

	auto itr = this->heartsTimes_.begin();

	while (itr != this->heartsTimes_.end()){

		*itr += elapsedTime;
		if (*itr < this->DRAW_RANGE_TIME_){
			itr++;
			continue;
		}

		itr = this->heartsTimes_.erase(itr);

	}

}

void HeartBeam::Draw(){

	if (this->heartsTimes_.size() <= 0) return;

	for (auto time : this->heartsTimes_){
		{
			float scale = (float)time / (float)this->DRAW_RANGE_TIME_;
			if (scale <= 0.0f) break;

			int alphaInt = time % (this->DRAW_RANGE_TIME_ / 2);
			if (time / (this->DRAW_RANGE_TIME_ / 2)){
				alphaInt = (this->DRAW_RANGE_TIME_ / 2) - alphaInt;
			}

			float alpha = (float)alphaInt / (float)(this->DRAW_RANGE_TIME_ / 2);

			SpriteBatch.Draw(*(this->sp_),this->pos_,alpha,Vector3_Zero,
				Vector3(426.0f / 2.0f, 426.0f / 2.0f,0.0f),scale * 2.0f);

		}
	}

}

void HeartBeam::LetsBeam(){

	this->heartsTimes_.clear();
	
	int inTime = 0;

	for (int i = 0; i < 10;i++){

		this->heartsTimes_.push_back(inTime);
		inTime -= 250;

	}

}