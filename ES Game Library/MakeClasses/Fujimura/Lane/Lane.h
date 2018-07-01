#pragma once
#include <d3dx9.h>
#include <vector>
#include "../../../ESGLib.h"
#include "BaseLane.h"

class JudgeBomb;
class JudgementContext;

//ŽÀŽ¿ƒŒ[ƒ“‚²‚Æ‚ÌNoteManagerŒN
class Lane : public BaseLane{

public:

	Lane(Vector3 inPos, JudgementContext* inJudge, int mouseNum);
	~Lane();

	virtual void Update(LONG nowTime);
	virtual void Draw(LONG nowTime);

	virtual void Accept(VISITORMETHOD visitorMethod);

	Vector2 GetSize(){ return this->SIZE_; }
	void GetLaneVectol(Vector3 &startPos, Vector3 &hitPos);

private:

	const Vector2 SIZE_;
	const Vector3 POS_;


	int mouseNum_;

	JudgementContext* judge_;
	JudgeBomb* bomb_;

};