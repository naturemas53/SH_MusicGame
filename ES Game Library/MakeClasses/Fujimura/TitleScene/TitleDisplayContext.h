#pragma once

class TitleDisplayScene;

class TitleDisplayContext{

public:

	TitleDisplayContext();
	~TitleDisplayContext();

	void Update();
	void Draw();

private:

	TitleDisplayScene* scene_;

};