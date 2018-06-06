#pragma once
#include "RawInput.h"

const int MOUSE_BUTTONS_MAX = 5;

class MouseStatus : public MouseListeners
{
	bool buttons[MOUSE_BUTTONS_MAX];
	int m_diff_x, m_diff_y, m_diff_w;
public:
	bool button(unsigned n) const { return n < MOUSE_BUTTONS_MAX ? buttons[n] : false; }
	int diff_x(void) const { return m_diff_x; }
	int diff_y(void) const { return m_diff_y; }
	int diff_w(void) const { return m_diff_w; }
	void reset(void) { m_diff_x = m_diff_y = m_diff_w = 0; }

	MouseStatus(void)
	{
		m_diff_x = m_diff_y = m_diff_w = 0;
		memset(buttons, 0, MOUSE_BUTTONS_MAX * sizeof(bool));
	}

	void OnClickDown(int idbutton)
	{
		if (idbutton < MOUSE_BUTTONS_MAX)
			buttons[idbutton] = true;
	}

	void OnClickUp(int idbutton)
	{
		if (idbutton < MOUSE_BUTTONS_MAX)
			buttons[idbutton] = false;
	}

	void OnCursorMove(int x, int y)
	{
		m_diff_x += x;
		m_diff_y += y;
	}

	void OnWheelMove(int w)
	{
		m_diff_w += w;
	}
};

const unsigned RI_BUTTON_MAX = 256;

class ButtonStatus : public ButtonListeners
{
	bool buttons[RI_BUTTON_MAX];
public:
	bool key(unsigned buttoncode) const { return buttoncode < RI_BUTTON_MAX ? buttons[buttoncode] : false; }
	ButtonStatus(void) { memset(buttons, 0, RI_BUTTON_MAX * sizeof(bool)); }
	void OnButtonDown(int vk)
	{
		if (vk < RI_BUTTON_MAX)
			buttons[vk] = true;
	}

	void OnButtonUp(int vk)
	{
		if (vk < RI_BUTTON_MAX)
			buttons[vk] = false;
	}
};
