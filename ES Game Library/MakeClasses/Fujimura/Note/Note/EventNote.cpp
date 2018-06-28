#include "EventNote.h"
#include "../../JukeBox.h"

EventNote::EventNote(LONG inTiming) : Note(inTiming,EVENTNOTE){

}

EventNote::~EventNote(){


}

void EventNote::Update(){}

void EventNote::Draw(SPRITE sp,Vector3 pos){  

	float scale = 0.5f;
	float angle = 90.0f * BgmComponent.GetRhythmRate();
	float sin = MathHelper_Sin(angle);
	scale += (1.0f - sin) * 0.3f;

	SpriteBatch.Draw(*sp,pos,1.0f,Vector3_Zero,Vector3(867.0f / 2.0f,753.0f / 2.0f,0.0f),scale);

}