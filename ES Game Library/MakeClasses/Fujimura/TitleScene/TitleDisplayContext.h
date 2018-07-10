#pragma once

class TitleDisplayScene;

class TitleDisplayContext{

public:

	TitleDisplayContext();
	~TitleDisplayContext();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

private:

	TitleDisplayScene* scene_;

};