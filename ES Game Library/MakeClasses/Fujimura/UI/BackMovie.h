#pragma once
#include "../../../ESGLib.h"

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

};