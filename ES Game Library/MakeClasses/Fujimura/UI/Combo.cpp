#include "Combo.h"

Combo::Combo(){


}

Combo::~Combo(){


}

void Combo::Update(){


}

void Combo::Draw(){



}

void Combo::ChangeCombo(JUDGE judge){

	if (judge == MISS){
		this->combo_ = 0;
		for (auto method : this->comboBreakMethods_) method();
		return;
	}

	this->combo_++;

	for (auto methodPair : this->rankUpMethods_){
		if (methodPair.first(this->combo_)) methodPair.second();
	}

}

void Combo::EntryRankUpMethod(ISRUN teams, NOTICE notice){
	std::pair<ISRUN, NOTICE> pair;
	pair.first = teams;
	pair.second = notice;

	this->rankUpMethods_.push_back(pair);
}

void Combo::EntryComboBreakMethod(NOTICE notice){
	this->comboBreakMethods_.push_back(notice);
}