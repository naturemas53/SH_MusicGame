#include "PerfectBomb.h"
#include "../DataSingleton.h"

PerfectBomb::PerfectBomb(){

	this->degreeRandom_ = std::uniform_real_distribution<float>(0.0f,360.0f);
	this->rotateRandom_ = std::uniform_real_distribution<float>(0.0f,360.0f);
	this->timeRandom_ = std::uniform_int_distribution<int>(100,300);

}

PerfectBomb::~PerfectBomb(){

}

void PerfectBomb::Update(){

	if(this->lights_.size() <= 0) return;

	this->time_ += GameTimer.GetElapsedMilliSecond();

	auto itr = this->lights_.begin();

	while(itr != this->lights_.end()){
	
		if(this->time_ >= itr->time_){
		itr = this->lights_.erase(itr);
		continue;
		}

		itr++;

	}

}

void PerfectBomb::Draw(Vector3 pos){

	if(this->lights_.size() <= 0) return;

	SPRITE sp = Data.perfectSp_;
	
	Light data;
	for(int i = 0;i < this->lights_.size();i++){
	
		data = this->lights_[i];
		float timeRate = (float)this->time_ / (float)data.time_;

		Vector3 drawPos = pos;
		drawPos.x += MathHelper_Cos(data.degrees_) * (100.0f * timeRate);
		drawPos.y += MathHelper_Sin(data.degrees_) * (100.0f * timeRate);

		SpriteBatch.Draw(*sp,drawPos,data.rect_,1.0f - timeRate,Vector3(0.0f,0.0f,360.0f * timeRate ),Vector3(25.0f,25.0f,0.0f),1.0f);

	}

}

void PerfectBomb::ReadyBomb(){

	this->lights_.clear();
	this->time_ = 0;

	Light light;
	int instanceCounts = 10;
	for(int i = 0;i < instanceCounts;i++){
	
		light.degrees_ = i * (360.0f / (float)instanceCounts);
		light.baseRotate_ = this->rotateRandom_(this->random_);
		light.time_ = this->timeRandom_(this->random_);
		{
		int x = this->random_() % 4;
		light.rect_ = RectWH( 50 * x,0,50,50);
		}

		this->lights_.push_back(light);
	
	}

}