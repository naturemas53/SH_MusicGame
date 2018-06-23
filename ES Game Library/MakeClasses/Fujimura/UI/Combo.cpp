#include "Combo.h"

Combo::Combo(){

	this->combo_ = 0;
	this->font_ = GraphicsDevice.CreateDefaultFont();
}

Combo::~Combo(){


}

void Combo::Update(){


}

void Combo::Draw(){

	if (this->combo_ <= 0) return;

	Color color = Color(255, 255, 255);
	if (this->combo_ >= 50) color = Color(255, 0, 0);
	if (this->combo_ >= 100) color = Color(255, 255, 0);

	SpriteBatch.DrawString(this->font_,Vector2_Zero,color,_T("%d Combo"),this->combo_);

}

void Combo::ChangeCombo(JUDGE judge){

	if (judge == NONE) return;

	if (judge == MISS){
		this->combo_ = 0;
		for (auto method : this->comboBreakMethods_) method();
		return;
	}

	this->combo_++;

	for (auto methodPair : this->comboUpMethods_){
		if (methodPair.first(this->combo_)) methodPair.second();
	}

}

void Combo::EntryComboUpMethod(ISRUN teams, NOTICE notice){
	std::pair<ISRUN, NOTICE> pair;
	pair.first = teams;
	pair.second = notice;

	this->comboUpMethods_.push_back(pair);
}

void Combo::EntryComboBreakMethod(NOTICE notice){
	this->comboBreakMethods_.push_back(notice);
}