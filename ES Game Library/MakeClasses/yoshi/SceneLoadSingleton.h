#pragma once
#include <thread>
#include <future>

class SceneLoadSingleton{

public:

	static SceneLoadSingleton& GetInstance(){

		static SceneLoadSingleton instance;
		return instance;

	}

	bool IsComplete(int* scenePointer);
	void SetAsyncLoad(std::future<int> future){ this->gameScene_ = future.share(); }
	
	~SceneLoadSingleton();

private:

	SceneLoadSingleton();

	std::shared_future<int> gameScene_;
 
};

#define AsyncLoadScene SceneLoadSingleton::GetInstance()