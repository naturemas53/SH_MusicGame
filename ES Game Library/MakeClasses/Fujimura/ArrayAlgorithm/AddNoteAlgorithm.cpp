#include "AddNoteAlgorithm.h"
#include "../Note/Note/Note.h"

/**
* @file AddNoteAlgorithm.cpp
* @brief ノート配列ソート、要素追加クラス　実装部
* @author So Fujimura
* @date 2018/07/05
*/

/**
* @brief Noteインスタンス要素追加関数
* @param (insertnote) 新しく追加するノート
* @param (notes) 今入ってるノートの集まり
* @return void
* @detail 1つ１つの要素を見ていって、
*		  適切な場所に挿入する関数です。
*/
void AddNoteAlgorithm::Execution(std::vector<Note*>& notes, Note* insertnote){
	
	// そもそも1つも入ってないなら比較もせずに追加
	if (notes.size() == 0){
		notes.push_back(insertnote);
		return;
	}

	int targetTiming = insertnote->GetTiming();
	auto itr = notes.begin();

	while (itr != notes.end()){

		// １つ１つの要素と比較し、
		// 今見てる要素のタイミングが
		// 挿入しようとしてるタイミングより遅ければ
		// その要素の手前に挿入
		if (targetTiming < (*itr)->GetTiming()){
			notes.insert(itr, insertnote);
			return;
		}

		itr++;

	}

	//ここまで来た場合はどの要素よりも遅かった
	notes.push_back(insertnote);

}