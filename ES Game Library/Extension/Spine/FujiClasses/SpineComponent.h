#pragma once

#include "SPINE.h"

#include <spine\spine.h>
#include <map>
#include <string>
#include <vector>

#ifndef _INC_SPINE
#define _INC_SPINE
#endif

class SpineComponent{

public:

	static SpineComponent& GetInstance(){

		static SpineComponent instance;

		return instance;

	}

	~SpineComponent();
	
	ISpine* CreateSpineFromFile(std::string folderpath,std::string charactorname,bool isprofessional = false,float scale = 1.0f);
	ISpine* CreateSpineToCharactorName(std::string charactorname);

	void ReleaseSpine(ISpine* self);
	void ReleaseSpineResouse(std::string charactorname);
	void ReleaseAllSpines();
	void ReleaseAllSpineResouses();

private:

	struct SpineResouses{

		spAtlas* atlas;
		spSkeletonData* skeletonData;
		spAnimationStateData* animationStateData;

	};

	SpineComponent();

	std::map<std::string, SpineResouses> ressouses_;
	std::vector<ISpine*> spineinstances_;

};

#define Spine SpineComponent::GetInstance()