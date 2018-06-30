#include "SceneLoadSingleton.h"
#include <chrono>

SceneLoadSingleton::SceneLoadSingleton(){



}

SceneLoadSingleton::~SceneLoadSingleton(){


}

bool SceneLoadSingleton::IsComplete(int* scenePointer){

	if (this->gameScene_.wait_for(std::chrono::seconds(0)) == std::future_status::ready){
		*scenePointer = this->gameScene_.get();
		return true;
	}

	return false;

}