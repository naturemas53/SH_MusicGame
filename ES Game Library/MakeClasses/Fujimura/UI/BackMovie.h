#pragma once
#include "../../../ESGLib.h"
#include "../../yoshi/effect/Noise.h"
#include "../../yoshi/effect/Scan_Line.h"


class  BackMovie
{
public:

	 BackMovie();
	~ BackMovie();

	void Update();
	void Draw();
	void MovieChange();
	void MovieReset();

private:

	std::vector<MEDIA> movies_;
	typedef std::vector<MEDIA>::iterator MovieItr;
	MovieItr nowmovie_;


	int noise_time;
	
	RENDERTARGET offscreen[2];

	Noise effect_noise;
	Scan_Line effect_scan_line;
	


};