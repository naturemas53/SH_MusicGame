/*
    RAW input demo code
    - This code handles multiple HID devices individually.

    by MUTATE Systems 2018
*/

#pragma once
#include "RawInput.h"

// Examples of raw input detectors and listeners

const int MOUSE_BUTTONS_MAX = 5;

class RiMouseState : public RiMouseListener {
    bool m_Buttons[MOUSE_BUTTONS_MAX];
    int m_diffX, m_diffY, m_diffW;
public:
    bool button(unsigned n) const { return n < MOUSE_BUTTONS_MAX ? m_Buttons[n] : false; }
    int diffX(void) const { return m_diffX; }
    int diffY(void) const { return m_diffY; }
    int diffW(void) const { return m_diffW; }
    void reset(void) { m_diffX = m_diffY = m_diffW = 0; }

    RiMouseState(void) {
        m_diffX = m_diffY = m_diffW = 0;
        memset(m_Buttons, 0, MOUSE_BUTTONS_MAX * sizeof(bool));
    }

    void onKeyDown(int idButton) {
        if(idButton < MOUSE_BUTTONS_MAX) m_Buttons[idButton] = true;
    }
    void onKeyUp(int idButton)  {
        if(idButton < MOUSE_BUTTONS_MAX) m_Buttons[idButton] = false;
    }
    void onCursorMove(int x, int y) {
        m_diffX += x; m_diffY += y;
    }
    void onWheelMove(int w) {
        m_diffW += w;
    }
};

const unsigned RI_KEYCODE_MAX = 256;

class RiKeyboardState : public RiListener {
    bool m_Keys[RI_KEYCODE_MAX];
public:
    bool key(unsigned keycode) const { return keycode < RI_KEYCODE_MAX ? m_Keys[keycode] : false; }
    RiKeyboardState(void) { memset(m_Keys, 0, RI_KEYCODE_MAX * sizeof(bool)); }
    void onKeyDown(int vk) {
        if(vk < RI_KEYCODE_MAX) m_Keys[vk] = true;
    }
    void onKeyUp(int vk) {
        if(vk < RI_KEYCODE_MAX) m_Keys[vk] = false;
    }
};

