#pragma once
#include <Windows.h>

class MultiMouseSingleton{

public:

	static MultiMouseSingleton& GetInstance(){

		static MultiMouseSingleton instance;
		return instance;

	}

	~MultiMouseSingleton(){};

	static void MultiMouseSingleton::SetRawInputProc(HWND hwnd,WNDPROC wndproc);
	static LRESULT CALLBACK MultiMouseSingleton::SubWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnRawInput(WPARAM wParam, LPARAM lParam){};

private:

	MultiMouseSingleton(){};
	static WNDPROC mainWndProc_;

};

#define MultiMouse MultiMouseSingleton::GetInstance()