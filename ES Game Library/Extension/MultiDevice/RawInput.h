#pragma once
#include <map>
#include <vector>
#include <Windows.h>

typedef HANDLE HRIDEV;

/*ボタンを押すリスナー*/
class ButtonListeners
{
public:
	virtual void onKeyDown(int click_down) {};
	virtual void onKeyUp(int click_up) {};
	HRIDEV m_hdevLast;
};

/*マウスを動す、ホイールを回すリスナー*/
class MouseListeners : public ButtonListeners
{
public:
	virtual void OnCursorMove(int move_x, int move_y) {};
	virtual void OnWheelMove(int w) {};
	HRIDEV m_hdevLast;
};

const HRIDEV RIDEV_DEFAULT = (HRIDEV)0xffffffff;

class RawInputReceiver
{
	std::map<HRIDEV, MouseListeners*> m_MouseListener;
	std::map<HRIDEV, ButtonListeners*> m_ButtonListener;

	static LRESULT CALLBACK subclassProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam, UINT_PTR uidsubclass, DWORD_PTR dwrefdata);
public:
	RawInputReceiver(void);
	~RawInputReceiver();
	
	bool AddMouseListener(HRIDEV, MouseListeners*);
	bool AddButtonListener(HRIDEV, ButtonListeners*);

	static bool Initialize(void);

	bool SetTargetWindow(void* hwnd);
	bool UnsetTargetWindow(void* hwnd);

	void InitDeviceStatus(void);

	void OnRawInput(WPARAM wParam, LPARAM lParam);
};

template<class T>
class RiDetector : public T 
{
	std::vector<HRIDEV> m_hdevFound;
	HRIDEV m_lastKeyDown;
public:
	RiDetector(void) { m_lastKeyDown = RIDEV_DEFAULT; }
	size_t getDeviceCount(void) const { return m_hdevFound.size(); }
	HRIDEV getDeviceID(unsigned n) const {
		return n < m_hdevFound.size() ? m_hdevFound[n] : RIDEV_DEFAULT;
	}
	void onKeyDown(int idButton)  
	{
		m_lastKeyDown = m_hdevLast;
	}
	void onKeyUp(int idButton)  
	{
		if (m_lastKeyDown != m_hdevLast) return;
		for (auto i = m_hdevFound.begin(); i != m_hdevFound.end(); i++)
			if (m_hdevLast == (*i))
				return;
		m_hdevFound.push_back(m_hdevLast);
	}
};