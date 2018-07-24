/**
* @file Lane.cpp
* @brief レーンクラス　実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "Lane.h"
#include "../DataSingleton.h"
#include "../Judgement/JudgementContext.h"
#include "JudgeBomb.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"

/**
* @brief Laneコンストラクタ
* @param (inPos) ノートの終点座標
* @param (inJudge) judgementContextポインタの登録
* @param (mouseNum) 何番目に登録されたマウスを見るか
* @return void
* @detail Laneコンストラクタの初期化関数になります。
*/
Lane::Lane(Vector3 inPos, JudgementContext* inJudge, int mouseNum) :
SIZE_(Vector2(0.0f,0.0f)),
POS_(inPos){

	this->judge_ = inJudge;

	//判定が決まったら、判定したノートを消す
	this->judge_->EntryJudgeMethod([this](JUDGE judge){ 
	
		auto itr = this->notes_.begin();
		if (itr == this->notes_.end()) return;

		delete (*itr);
		this->notes_.erase(itr);

	});


	this->bomb_ = new JudgeBomb();

	//判定に応じたボムを出す
	this->judge_->EntryJudgeMethod([&](JUDGE judge){
		bomb_->NoticeJudge(judge);
	});

	this->mouseNum_ = mouseNum;

}

Lane::~Lane(){

	delete this->bomb_;

}

/**
* @brief Lane更新関数
* @param (nowTime) 曲の現在時間
* @return void
* @detail 配列の先頭のノートをJudgementContextに判定してもらいます。
*/
void Lane::Update(LONG nowTime){

	this->bomb_->Update();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	(*itr)->Update();
	this->judge_->judgeNote((*itr), nowTime,MultiMouse.GetInputData(this->mouseNum_));

}

/**
* @brief Lane描画関数
* @param (nowTime) 曲の現在時間
* @return void
* @detail Laneに入っているノートを曲の時間に合わせ、描画します。
*/
void Lane::Draw(LONG nowTime){

	this->bomb_->Draw(this->POS_);

	for (auto note : this->notes_){
		//画面内に移るノートだけ描画したいので、
		//falseが返ってきたら描画処理を終了
		if (!(NoteDrawComponent.Draw(note, this, nowTime)) )break;
	}
}

/**
* @brief 訪問関数を受け入れする関数
* @param (visit) 訪問する関数
* @return void
* @detail Visitor関数を受け入れます。
*/
void Lane::Accept(VISITORMETHOD visit){visit(this);}

/**
* @brief レーンの始点終点を取得する関数
* @param (startPos) レーンの始点を受け取る変数
* @param (endPos) レーンの終点を受け取る変数
* @return void (ただし、引数として渡した変数にレーンの始点と終点が入る)
* @detail レーンの始点と終点を取得します。
*		  ただし、2つ同時に取得するので
*		  戻り値ではなく、引数に渡した変数に入ります。
*/
void Lane::GetLaneVectol(Vector3 &startPos, Vector3 &hitPos){

	startPos = this->POS_;
	startPos.x += this->SIZE_.x / 2.0f;
	//上から降ってくるので0
	startPos.y = 0.0f;

	hitPos = this->POS_;
	hitPos.x += this->SIZE_.x / 2.0f;
	hitPos.y += this->SIZE_.y / 2.0f;

}