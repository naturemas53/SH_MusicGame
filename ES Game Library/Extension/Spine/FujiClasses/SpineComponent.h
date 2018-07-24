#pragma once

/**
* @file SpineComponent.h
* @brief Spine�C���X�^���X�̃��\�[�X�Ǘ�
* @author So Fujimura
* @date 2018/06/01
*/

#include "SPINE.h"

#include <spine\spine.h>
#include <map>
#include <string>
#include <vector>

#ifndef _INC_SPINE
#define _INC_SPINE
#endif

/**
* ClassName SpineComponent
* Spine�C���X�^���X�̃��\�[�X�Ǘ�
* �����������炱�񂪂炪�肻���Ȃ̂�
* �V���O���g���ɂ��܂����B
*/
class SpineComponent{

public:

	static SpineComponent& GetInstance(){

		static SpineComponent instance;

		return instance;

	}

	~SpineComponent();
	
	ISpine* CreateSpineFromFile(std::string folderpath,std::string charactorname,float scale = 1.0f);
	ISpine* CreateSpineToCharactorName(std::string charactorname);

	void ReleaseSpine(ISpine* instance);
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

#define SpineSingleton SpineComponent::GetInstance()