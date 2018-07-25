#pragma once
#include <d3dx9.h>

typedef D3DXVECTOR3 Vector3;

class DinamicScaleInterface{

public:

	DinamicScaleInterface(){};
	virtual ~DinamicScaleInterface(){};

	virtual void Replay() = 0;

	virtual void AddScalePoint(int ms,Vector3 Scale) = 0;
	virtual bool HasAddScalePoint(int ms, Vector3 Scale) = 0;
	virtual void RemoveScalePoint(int ms, Vector3 Scale) = 0;

};