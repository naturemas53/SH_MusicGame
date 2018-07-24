#include "DeleteNoteAlgorithm.h"
#include "../Note/Note/Note.h"

/**
* @file DeleteNoteAlgorithm.cpp
* @brief ノート配列ソート、要素解放クラス　実装部
* @author So Fujimura
* @date 2018/07/05
*/

/**
* @brief Noteインスタンス要素追加関数
* @param (insertnote) 新しく追加するノート
* @param (notes) 今入ってるノートの集まり
* @return void
* @detail 指定された要素を探し、
*		  あればその要素のインスタンスを開放する
*         関数です。
*/
void DeleteNoteAlgorithm::Execution(std::vector<Note*>& notes, Note* note){

	auto itr = std::find(notes.begin(),notes.end(),note);
	if (itr != notes.end()) delete note;

}