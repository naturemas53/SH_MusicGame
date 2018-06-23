#pragma once
#include <d3dx9.h>
#include <vector>

enum JUDGE;
class Combo;
class BackMovie;

class UI{

public:

	UI();
	~UI();

	void Update(DWORD nowTime);
	void Draw(DWORD nowTime);

	void NoticeJudge(JUDGE value);

private:

	int score_;
	
	Combo* combo_;
	BackMovie* movie_;

};