#pragma comment (lib, "comctl32.lib")
#include "RawInput.h"
#include <CommCtrl.h>

RawInputReceiver::RawInputReceiver(void)
{}

RawInputReceiver::~RawInputReceiver()
{
	InitDeviceStatus();
}

const int misub_class_id = 1;

/**/
LRESULT CALLBACK RawInputReceiver::subclassProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam,
	UINT_PTR uidsubclass, DWORD_PTR dwrefdata)
{
	if (umsg == WM_INPUT)
	{
		RawInputReceiver* pRecv = (RawInputReceiver*)dwrefdata;
		pRecv->OnRawInput(wparam, lparam);
	}
	return DefSubclassProc(hwnd, umsg, wparam, lparam);
}

bool RawInputReceiver::SetTargetWindow(void* hwnd)
{
	return SetWindowSubclass((HWND)hwnd, subclassProc, misub_class_id, (DWORD)this) != 0;
}

bool RawInputReceiver::UnsetTargetWindow(void* hwnd)
{
	return RemoveWindowSubclass((HWND)hwnd, subclassProc, misub_class_id) != 0;
}

void RawInputReceiver::InitDeviceStatus(void)
{
	m_MouseListener.clear();
	m_ButtonListener.clear();
}

bool RawInputReceiver::AddMouseListener(HRIDEV hdev, MouseListeners* ml)
{
	m_MouseListener[hdev] = ml;
	return true;
}

bool RawInputReceiver::AddButtonListener(HRIDEV hdev, ButtonListeners* kl)
{
	m_ButtonListener[hdev] = kl;
	return true;
}

/*マウスの情報を取得する処理*/
void RawInputReceiver::OnRawInput(WPARAM wparam, LPARAM lparam)
{
	UINT datasize = 0;
	HRAWINPUT hrawinput = (HRAWINPUT)lparam;
	GetRawInputData(hrawinput, RID_INPUT, NULL, &datasize, sizeof(RAWINPUTHEADER));
	
	std::vector<BYTE> rim(datasize);

	GetRawInputData(hrawinput, RID_INPUT, &rim[0], &datasize, sizeof(RAWINPUTHEADER));
	const RAWINPUT *raw = (const RAWINPUT*)(&rim[0]);



	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		MouseListeners* ml = m_MouseListener[raw->header.hDevice];
		if (!ml) ml = m_MouseListener[RIDEV_DEFAULT];
		

		if (ml)
		{
			ml->m_hdevLast = raw->header.hDevice;
			if (raw->data.mouse.lLastX || raw->data.mouse.lLastY)
				ml->OnCursorMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
			USHORT bf = raw->data.mouse.usButtonFlags;
			if (bf & 1)   /*Left Button*/
				ml->onKeyDown(0);
			if (bf & 2)   
				ml->onKeyUp(0);
			if (bf & 4)   /*Right Button*/
				ml->onKeyDown(1);
			if (bf & 8)
				ml->onKeyUp(1);
			if (bf & 0x10)  /*Middle Button*/
				ml->onKeyDown(2);
			if (bf & 0x20)
				ml->onKeyUp(2);

			if (bf & 0x40)
				ml->onKeyDown(3);
			if (bf & 0x80)
				ml->onKeyUp(3);
			if (bf & 0x100)
				ml->onKeyDown(4);
			if (bf & 0x200)
				ml->onKeyUp(4);

			if (bf & 0x400)  /*Wheel +-*/
			{
				short wheel = (short)raw->data.mouse.usButtonData;
				if (wheel > 0)
					ml->OnWheelMove(1);
				else if (wheel < 0)
					ml->OnWheelMove(-1);
			}
		}
	}

}

/*マウスの初期化*/
bool RawInputReceiver::Initialize(void)
{
	RAWINPUTDEVICE device[2] = { 0 };
	device[0].usUsagePage = 0x01;
	device[0].usUsage = 0x02;
	device[1].usUsagePage = 0x01;
	device[1].usUsage = 0x06;
	RegisterRawInputDevices(device, 2, sizeof(RAWINPUTDEVICE));
	return true;
}