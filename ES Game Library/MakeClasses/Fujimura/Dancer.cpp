#include "Dancer.h"
#include "HeartBeam.h"

Dancer::Dancer(){

	this->sideStepSpine_ = SpineSingleton.CreateSpineFromFile("usakyara2/SideStep","usakyara2_sideStep",0.5f);
	this->sideStepSpine_->SetPosition(Vector2(660.0f,480.0f));

	this->sideStepSpine_->FlipY();
	this->sideStepSpine_->SetAnimation(0,"animation",1);

	this->heartSpine_ = SpineSingleton.CreateSpineFromFile("usakyara2/Heart","usakyara2_Heart",0.5f);
	this->heartSpine_->SetPosition(Vector2(640.0f,480.0f));

	this->heartSpine_->FlipY();
	this->heartSpine_->EntryAnimationEndMethod([this](){
	
		this->drawSpine_ = this->sideStepSpine_;
		
	});

	this->drawSpine_ = this->sideStepSpine_;

	this->beam_ = new HeartBeam();
}

Dancer::~Dancer(){

	SpineSingleton.ReleaseSpine(this->sideStepSpine_);
	SpineSingleton.ReleaseSpineResouse("usakyara2_sideStep");
	SpineSingleton.ReleaseSpine(this->heartSpine_);
	SpineSingleton.ReleaseSpineResouse("usakyara2_Heart");

	delete this->beam_;

}

void Dancer::Update(DWORD nowTime){

	this->beam_->Update();
	

	this->sideStepSpine_->Update();
	this->heartSpine_->Update();

}

void Dancer::Draw(DWORD nowTime){

	SpriteBatch.Begin();
	this->beam_->Draw();
	SpriteBatch.End();
	this->drawSpine_->Draw();

//	GraphicsDevice.ClearStencil();
	GraphicsDevice.ClearZBuffer();
}

void Dancer::SetPerformanceAnimation(){

	this->beam_->LetsBeam();

	this->drawSpine_ = this->heartSpine_;
	this->heartSpine_->SetAnimation(0,"animation",0);
	this->heartSpine_->AddAnimation(0,nullptr,2.0f,0);

}

void Dancer::SetMissAnimation(){

}