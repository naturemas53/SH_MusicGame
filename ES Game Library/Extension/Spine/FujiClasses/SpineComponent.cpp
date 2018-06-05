#include "SpineComponent.h"
#include <algorithm>
#include <string>
#include <locale> 
#include <codecvt>
#include <spine\extension.h>
#include <typeinfo>
#include "../../../ESGLib.h"

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path) {

	std::string str = path;
	std::wstring wstr;

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	wstr = cv.from_bytes(str);

	self->rendererObject = GraphicsDevice.CreateSpriteFromFile(wstr.c_str());	//set user class or record pointer
	self->width = ((SPRITE)self->rendererObject)->GetWidth();
	self->height = ((SPRITE)self->rendererObject)->GetHeight();

}

void _spAtlasPage_disposeTexture(spAtlasPage* self) {
	//dispose self->rendererObject

	//現時点では先にリソース解放をやってくれてるおかげでエラーになるっぽいので、
	//改良ができるまでそのままにします
	/*
	SPRITE sp = (SPRITE)self->rendererObject;
	GraphicsDevice.ReleaseSprite(sp);
	*/

	self->rendererObject = 0;
}

char* _spUtil_readFile(const char* path, int* length){

	return _spReadFile(path, length);

}
SpineComponent::SpineComponent(){
	GraphicsDevice.SetRenderState(CullMode_None);
}

SpineComponent::~SpineComponent(){

	this->ReleaseAllSpines();
	this->ReleaseAllSpineResouses();

}

ISpine* SpineComponent::CreateSpineFromFile(std::string folderpath, std::string charactorname,float scale){

	ISpine* instance = this->CreateSpineToCharactorName(charactorname);

	if (typeid(instance) == typeid(CSpine*)){ return instance; }

	//一回作っちゃってるんで消してからもっかい
	this->ReleaseSpine(instance);

	try{

		std::string basepath = folderpath + "/";
		std::string atlaspath = basepath + charactorname + ".atlas";
		spAtlas* atlas = spAtlas_createFromFile(atlaspath.c_str(), 0);
		if (atlas == NULL) throw("atlas load failed");

		spSkeletonJson* json = spSkeletonJson_create(atlas);
		json->scale = scale;
		std::string jsonpath = basepath + charactorname + "-ess.json";
		spSkeletonData* skeletonData = spSkeletonJson_readSkeletonDataFile(json,jsonpath.c_str());
		spSkeletonJson_dispose(json);
		if (skeletonData == NULL) throw("json load failed");

		spAnimationStateData* animeStateData = spAnimationStateData_create(skeletonData);
		if (animeStateData == NULL) throw("animeStateData load failed");

		this->ressouses_[charactorname].atlas = atlas;
		this->ressouses_[charactorname].skeletonData = skeletonData;
		this->ressouses_[charactorname].animationStateData = animeStateData;

		instance = new CSpine(skeletonData, animeStateData);

	}
	catch(std::string errorcode){

		::OutputDebugStringA(errorcode.c_str());
		instance = new CNullSpine();

	}

	this->spineinstances_.push_back(instance);
	return instance;

}

ISpine* SpineComponent::CreateSpineToCharactorName(std::string charactorname,float scale){

	ISpine* instance;
	auto itr = this->ressouses_.begin();

	if ((itr = this->ressouses_.find(charactorname)) != this->ressouses_.end()){

		SpineResouses resouses = (*itr).second;
		instance = new CSpine(resouses.skeletonData, resouses.animationStateData);

	}
	else{

		instance = new CNullSpine();

	}

	this->spineinstances_.push_back(instance);
	return instance;

}

void SpineComponent::ReleaseSpine(ISpine* self){

	auto itr = std::find(this->spineinstances_.begin(),this->spineinstances_.end(),self);
	if (itr == this->spineinstances_.end()) return;

	delete (*itr);
	this->spineinstances_.erase(itr);

}
void SpineComponent::ReleaseSpineResouse(std::string charactorname){

	auto itr = this->ressouses_.find(charactorname);
	if (itr == this->ressouses_.end()) return;

	SpineResouses resouse = itr->second;

	spSkeletonData_dispose(resouse.skeletonData);
	spAnimationStateData_dispose(resouse.animationStateData);
	spAtlas_dispose(resouse.atlas);

	this->ressouses_.erase(itr);


};
void SpineComponent::ReleaseAllSpines(){

	for (auto data : this->spineinstances_) delete data;
	this->spineinstances_.clear();

}
void SpineComponent::ReleaseAllSpineResouses(){

	for (auto data : this->ressouses_){

		spSkeletonData_dispose(data.second.skeletonData);
		spAnimationStateData_dispose(data.second.animationStateData);
		spAtlas_dispose(data.second.atlas);

	}

	this->ressouses_.clear();

}

