#pragma once
#include "../../../ESGLib.h"
#include "../../yoshi/effect/Noise.h"
#include "../../yoshi/effect/Scan_Line.h"
#include "../UI/WhiteMap.h"


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

	void MovieUp();

	std::vector<MEDIA> movies_;
	typedef std::vector<MEDIA>::iterator MovieItr;
	MovieItr nowmovie_;


	int noise_time;
	
	RENDERTARGET offscreen_;
	WhiteMap white_;
	


};