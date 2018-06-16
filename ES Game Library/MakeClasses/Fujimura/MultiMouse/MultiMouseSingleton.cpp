#include "MultiMouseSingleton.h"
#include <functional>
WNDPROC MultiMouseSingleton::mainWndProc_ = nullptr;

void MultiMouseSingleton::SetRawInputProc(HWND windowhandle,WNDPROC wndproc){

	MultiMouseSingleton::mainWndProc_ = wndproc;
	SetWindowLong(windowhandle, GWL_WNDPROC, (LONG)MultiMouseSingleton::SubWindowProc);

}

LRESULT CALLBACK MultiMouseSingleton::SubWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	if (uMsg == WM_INPUT){
		::OutputDebugStringA("Get WM INPUT\n");
		MultiMouse.OnRawInput(wParam, lParam);
		return 0;
	}

	return MultiMouseSingleton::mainWndProc_(hWnd, uMsg, wParam, lParam);

}

