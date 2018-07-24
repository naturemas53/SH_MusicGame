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

	int noise_time;
	
	std::vector<MEDIA> movies_;
	typedef std::vector<MEDIA>::iterator MovieItr;
	MovieItr nowmovie_;

	RENDERTARGET offscreen_;

	enum CHANGE_STATE{

		NONE,
		CHANGEING,
		CHANGED

	}changeState_;
	MEDIA effectMovie_;

	//WhiteMap white_;
	


};