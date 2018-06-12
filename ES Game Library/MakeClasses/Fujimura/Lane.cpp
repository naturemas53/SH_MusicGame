#include "Lane.h"

Lane::Lane(Vector3 inPos) : 
SIZE_(Vector2(512.0f,100.0f)),
POS_(inPos){

}

Lane::~Lane(){



}

void Lane::Draw(){

	SpriteBatch.Draw(*this->sp_,this->POS_);

}