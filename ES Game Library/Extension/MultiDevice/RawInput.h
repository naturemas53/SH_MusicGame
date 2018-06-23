/*
    RAW input demo code
    - This code handles multiple HID devices individually.

    by MUTATE Systems 2018
*/

#pragma once
#include <map>
#include <vector>
#include <windows.h>

typedef HANDLE HRIDEV;

class RiListener {
public:
    virtual void onKeyDown(int vk) {};
    virtual void onKeyUp(int vk) {};
    HRIDEV m_hdevLast;
};

class RiMouseListener : public RiListener {
public:
    virtual void onCursorMove(int x, int y) {};
    virtual void onWheelMove(int w) {};
    HRIDEV m_hdevLast;
};

// If you don't use multiple keyboards or mice, you can use this handle.
const HRIDEV RIDEV_DEFAULT = (HRIDEV)0xffffffff;

class RawInputReceiver {
    std::map<HRIDEV, RiMouseListener*> m_MouseListeners;
    std::map<HRIDEV, RiListener*> m_KeyboardListeners;

    static LRESULT CALLBACK subclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
public:
    RawInputReceiver(void);
    ~RawInputReceiver();

    bool addMouseListener(HRIDEV, RiMouseListener*);
    bool addKeyboardListener(HRIDEV, RiListener*);

    // Must be called once before using this class.
    static bool initialize(void);

    // Set window handle to capture raw input message.
    bool setTargetWindow(void* hwnd);
    bool unsetTargetWindow(void* hwnd);

    // It needs to be called if you use multiple mice or keyboards.
    void initDeviceStatus(void);

    // If you implement window procedure, call it manually.
    // Otherwise, it needs not to be called. Call setTargetWindow().
    void onRawInput(WPARAM wParam, LPARAM lParam);
};

template<class T>
class RiDetector : public T {
    std::vector<HRIDEV> m_hdevFound;
    HRIDEV m_lastKeyDown;
public:
    RiDetector(void) { m_lastKeyDown = RIDEV_DEFAULT; }
    size_t getDeviceCount(void) const { return m_hdevFound.size(); }
    HRIDEV getDeviceID(unsigned n) const {
        return n < m_hdevFound.size() ? m_hdevFound[n] : RIDEV_DEFAULT;
    }
    void onKeyDown(int idButton) override {
        m_lastKeyDown = m_hdevLast;
    }
    void onKeyUp(int idButton) override {
        if(m_lastKeyDown != m_hdevLast) return;
        for(auto i = m_hdevFound.begin(); i != m_hdevFound.end(); i++)
            if(m_hdevLast == (*i))
                return;
        m_hdevFound.push_back(m_hdevLast);
    }
};
