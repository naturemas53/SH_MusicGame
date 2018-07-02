#pragma once

class TitleDisplayScene{

public:
	TitleDisplayScene(){};
	~TitleDisplayScene(){};

	virtual void LoadResource() = 0;
	virtual void ReleaseResource() = 0;
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual TitleDisplayScene* Update() = 0;
	virtual void Draw() = 0;

};