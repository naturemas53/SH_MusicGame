#pragma once

#include <spine\spine.h>
#include <d3dx9.h>
#include <functional>

/**
* @file SPINE.h
* @brief スパインを手ごろに使えるように
* @author So Fujimura
* @date 2018/06/01
*/
typedef D3DXVECTOR2 Vector2;

/**
* ClassName SpineEventNotice
* アニメーションの開始、終了、破棄などの
* イベントを受け取れるようにするためのクラス。
*/
class SpineEventNotice{

public:
	SpineEventNotice(){
		this->startMethod_ = [](){};
		this->endMethod_ = [](){};
	}
	~SpineEventNotice(){
	
	}

	void NoticeAnimationStart(){this->startMethod_();}
	void NoticeAnimationEnd(){this->endMethod_();}

	void EntryAnimationStartMethod( std::function<void()> method ){ this->startMethod_ = method; }
	void EntryAnimationEndMethod( std::function<void()> method ){ this->endMethod_ = method; }

private:

	std::function<void()> startMethod_;
	std::function<void()> endMethod_;

};

/**
* ClassName ISpine
* オブジェクトの座標設定、アニメーションの更新など
* Spineでの必要な動作をまとめたクラス。
*/
class ISpine : public SpineEventNotice{
public:
	virtual ~ISpine(){};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SetPosition(Vector2 pos) = 0;
	virtual Vector2 GetPosition() = 0;
	virtual void FlipX() = 0;
	virtual void FlipY() = 0;

	virtual void SetAnimation(int playtrack, const char* animename, int isloop, float mixDulation = 1.0f) = 0;
	virtual void SetEnptyAnimations(float mixDulation = 1.0f) = 0;
	virtual void AddAnimation(int playtrack, const char* animename, float delay, int isloop, float mixDulation = 1.0f) = 0;

	virtual void SetTimeScale(float timescale) = 0;

};

/**
* ClassName CSpine
* オブジェクトの座標設定、アニメーションの更新など
* Spineでの必要な動作をまとめたクラス。
*/
class CSpine : public ISpine{

public:

	CSpine(spSkeletonData* skeletonData,spAnimationStateData* animationStateData);
	virtual ~CSpine();

	virtual void Update();
	virtual void Draw();

	virtual void SetPosition(Vector2 pos){
		this->skeleton_->x = pos.x;
		this->skeleton_->y = pos.y;
	}
	virtual Vector2 GetPosition(){ return Vector2(this->skeleton_->x, this->skeleton_->y); }
	virtual void FlipX(){ this->skeleton_->flipX = !(this->skeleton_->flipX); }
	virtual void FlipY(){ this->skeleton_->flipY = !(this->skeleton_->flipY); }

	virtual void SetAnimation(int playtrack, const char* animename, int isloop, float mixDulation = 1.0f);
	virtual void SetEnptyAnimations(float mixDulation = 1.0f);
	virtual void AddAnimation(int playtrack, const char* animename, float delay, int isloop, float mixDulation = 1.0f);

	virtual void SetTimeScale(float timescale){ this->animasionstate_->timeScale = timescale; }

private:

	void RegionDraw(spSlot* slot, spAttachment* attachment, spColor* col, int blendmode);
	void MeshDraw(spSlot* slot, spAttachment* attachment, spColor* col, int blendmode);

	spSkeleton* skeleton_;
	spAnimationState* animasionstate_;

	spBone* bone;

};

/**
* ClassName CNullSpine
* 生成失敗時用のNULLクラス。
*/
class CNullSpine : public ISpine{

public:
	CNullSpine(){};
	virtual ~CNullSpine(){};

	virtual void Update(){};
	virtual void Draw(){};

	virtual void SetPosition(Vector2 pos){};
	virtual Vector2 GetPosition(){ return Vector2(0.0f, 0.0f); }
	virtual void FlipX(){};
	virtual void FlipY(){};

	virtual void SetAnimation(int playtrack, const char* animename, int isloop, float mixDulation = 1.0f){}
	virtual void SetEnptyAnimations(float mixDulation = 1.0f){}
	virtual void AddAnimation(int playtrack, const char* animename, float delay, int isloop, float mixDulation = 1.0f){}

	virtual void SetTimeScale(float timescale){}

	virtual void NoticeAnimationStart(){}
	virtual void NoticeAnimationEnd(){}

};