/**
* @file EventLane.cpp
* @brief イベントレーンクラス　実装部
* @author So Fujimura
* @date 2018/07/05
*/
#include "EventLane.h"
#include "Lane.h"
#include "../Judgement/JudgementContext.h"
#include "../ArrayAlgorithm/DeleteNoteAlgorithm.h"
#include "../MultiMouseDevice.h"
#include "../Note/DrawNote/NoteDrawSingleton.h"
#include "../Lane/JudgeBomb.h"
#include "../../yoshi/effect/Effect_Singleton.h"
#include <typeinfo>

/**
* @brief EventLaneコンストラクタ
* @param (JudgementContext) 判定インスタンスのポインタ
* @return void
* @detail EventLaneコンストラクタの初期化関数になります。
*/
EventLane::EventLane(JudgementContext* judgement){

	//シェーダー用のスクリーンを用意
	offscreen =  GraphicsDevice.CreateRenderTarget(1280, 720, PixelFormat_RGBA8888, DepthFormat_Unknown);
	this->postMethod_ = nullptr;

	this->judgement_ = judgement;

	//判定が返ってきたらノートを消す
	JUDGENOTICE notice = [this](JUDGE judge){

		std::vector<Note*>& notes = this->GetNoteList();
		auto itr = notes.begin();
		if (itr == notes.end()) return;

		DeleteNoteAlgorithm deletenote;
		deletenote.Execution(notes,(*itr));
		notes.erase(itr);

	};
	this->judgement_->EntryJudgeMethod(notice);

	this->bomb_ = new JudgeBomb();
	//ボム表示
	this->judgement_->EntryJudgeMethod([this](JUDGE judge){
		this->bomb_->NoticeJudge(judge);
	});

	//PERFERCTなどの判定の文字を、通常レーンのしたに出すので、
	//外から各通常レーンにVISITORMETHODを投げれる関数をもらって、
	//その関数に判定を表示する処理を投げます
	this->drawJudgeVisitor_ = [this](BaseLane* baselane){
		if (typeid(*baselane) != typeid(Lane)) return;

		Lane* lane = (Lane*)baselane;

		Vector3 startPos, hitPos;
		lane->GetLaneVectol(startPos, hitPos);
		this->bomb_->Draw(hitPos);

	};

}

EventLane::~EventLane(){

	delete this->bomb_;
}


/**
* @brief EventLane更新関数
* @param (nowTime) 曲の現在時間
* @return void
* @detail EventLaneにある様々な要素を更新します。
*/
void EventLane::Update(LONG nowTime){

	this->bomb_->Update();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	RawInputMouse& mouse = MultiMouse.GetInputData(0);
	this->judgement_->judgeNote((*itr),nowTime,mouse);

}

/**
* @brief EventLane描画関数
* @param (nowTime) 曲の現在時間
* @return void
* @detail EventLaneに入っているノートを
*		  「シェーダーをかけて」
*		  描画します。
*/
void EventLane::Draw(LONG nowTime){

	//まず判定の描画を各レーンの下に行います。
	SpriteBatch.Begin();
	if (this->postMethod_ != nullptr) this->postMethod_(this->drawJudgeVisitor_);
	SpriteBatch.End();

	auto itr = this->notes_.begin();
	if (itr == this->notes_.end()) return;

	//用意した別スクリーンにノートを描画します。
	GraphicsDevice.SetRenderTarget(offscreen);
	GraphicsDevice.Clear(Color(0,0,0,0));
	SpriteBatch.Begin();
	bool isDraw = NoteDrawComponent.Draw((*itr),this,nowTime);
	SpriteBatch.End();

	if (!isDraw) return;

	//順番にかけるシェーダーを配列に追加
	std::vector<Effect_Singleton::SHADER_NAME> comands_;

	//配列に追加した順番に、シェーダーを適用、
	//適用後の画像が返ってきます。
	RENDERTARGET onShaderScreen = Effect_Singleton::GetInstance().Image_On_Effect(comands_,offscreen);

	GraphicsDevice.SetDefaultRenderTarget();
	SpriteBatch.Begin();

	//DrawSimpleでやると、回転行列や拡大縮小行列、移動行列の情報が
	//残ったままなので、InitTransformで初期化
	SpriteBatch.InitTransform();

	SpriteBatch.DrawSimple(*onShaderScreen, Vector3_Zero,1.0f);

	SpriteBatch.End();

}

/**
* @brief VISITORMETHOD受け入れ関数
* @param (visit) 訪問関数
* @return void
* @detail EventLaneで処理をする関数を受け入れます。
*/
void EventLane::Accept(VISITORMETHOD visit){visit(this);}

/**
* @brief EventLane描画関数
* @param (nowTime) 曲の現在時間
* @return void
* @detail　
*/
void EventLane::EntryPostMethod(std::function<void(VISITORMETHOD)> postMethod){this->postMethod_ = postMethod;}