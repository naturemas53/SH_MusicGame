#pragma once
#include "NoteBomb.h"

class MissBomb : public NoteBomb{

public:

	MissBomb();
	~MissBomb();

	virtual void Update();
	virtual void Draw(Vector3 pos);

	virtual void ReadyBomb();

private:

};