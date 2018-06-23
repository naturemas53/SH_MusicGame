/*
    RAW input demo code
    - This code handles multiple HID devices individually.

    by MUTATE Systems 2018
*/

#pragma comment (lib, "comctl32.lib")
#include <vector>
#include "RawInput.h"
#include <Commctrl.h>

RawInputReceiver::RawInputReceiver(void)
{}

RawInputReceiver::~RawInputReceiver() {
    initDeviceStatus();
}

const int MiSubClassID = 1;

LRESULT CALLBACK RawInputReceiver::subclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
    UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    if(uMsg == WM_INPUT) {
        RawInputReceiver* pRecv = (RawInputReceiver*)dwRefData;
        pRecv->onRawInput(wParam, lParam);
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

bool RawInputReceiver::setTargetWindow(void* hwnd) {
    return SetWindowSubclass((HWND)hwnd, subclassProc, MiSubClassID, (DWORD_PTR)this) != 0;
}

bool RawInputReceiver::unsetTargetWindow(void* hwnd) {
    return RemoveWindowSubclass((HWND)hwnd, subclassProc, MiSubClassID) != 0;
}

void RawInputReceiver::initDeviceStatus(void) {
    m_MouseListeners.clear();
    m_KeyboardListeners.clear();
}

bool RawInputReceiver::addMouseListener(HRIDEV hdev, RiMouseListener* ml) {
    m_MouseListeners[hdev] = ml;
    return true;
}

bool RawInputReceiver::addKeyboardListener(HRIDEV hdev, RiListener* kl) {
    m_KeyboardListeners[hdev] = kl;
    return true;
}

void RawInputReceiver::onRawInput(WPARAM wParam, LPARAM lParam) {
    UINT dataSize = 0;
    HRAWINPUT hRawInput = (HRAWINPUT)lParam;
    GetRawInputData(
      hRawInput, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

    std::vector<BYTE> rim(dataSize);

    GetRawInputData(
      hRawInput, RID_INPUT, &rim[0], &dataSize, sizeof(RAWINPUTHEADER));

    const RAWINPUT *raw = (const RAWINPUT*)(&rim[0]);

    if (raw->header.dwType == RIM_TYPEMOUSE) {
        RiMouseListener* ml = m_MouseListeners[raw->header.hDevice];
        if(!ml) ml = m_MouseListeners[RIDEV_DEFAULT];

        if(ml) {
            ml->m_hdevLast = raw->header.hDevice;
            if(raw->data.mouse.lLastX || raw->data.mouse.lLastY)
                ml->onCursorMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
            USHORT bf = raw->data.mouse.usButtonFlags;
            if(bf & 1) // Left button
                ml->onKeyDown(0);
            if(bf & 2)
                ml->onKeyUp(0);
            if(bf & 4) // Right button
                ml->onKeyDown(1);
            if(bf & 8)
                ml->onKeyUp(1);
            if(bf & 0x10) // Middle button
                ml->onKeyDown(2);
            if(bf & 0x20)
                ml->onKeyUp(2);

            if(bf & 0x40) // 4th Button (Back)
                ml->onKeyDown(3);
            if(bf & 0x80)
                ml->onKeyUp(3);
            if(bf & 0x100) // 5th Button (Forward)
                ml->onKeyDown(4);
            if(bf & 0x200)
                ml->onKeyUp(4);

            if(bf & 0x400) { // Wheel +-
                short w = (short)raw->data.mouse.usButtonData;
                if(w > 0)
                    ml->onWheelMove(1);
                else if(w < 0)
                    ml->onWheelMove(-1);
            }
        }
    }
    else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
        bool bRelease = raw->data.keyboard.Flags & 1;
        int vk = raw->data.keyboard.VKey;

        RiListener* kl = m_KeyboardListeners[raw->header.hDevice];
        if(!kl) kl = m_KeyboardListeners[RIDEV_DEFAULT];

        if(kl) {
            kl->m_hdevLast = raw->header.hDevice;
            if(bRelease)
                kl->onKeyUp(vk);
            else
                kl->onKeyDown(vk);
        }
    }
}

bool RawInputReceiver::initialize(void) {
    RAWINPUTDEVICE device[2] = {0};
    device[0].usUsagePage = 0x01;
    device[0].usUsage = 0x02;
    device[1].usUsagePage = 0x01;
    device[1].usUsage = 0x06;
    RegisterRawInputDevices(device, 2, sizeof(RAWINPUTDEVICE));
    return true;
}
