#ifndef __WINDOWHOOKER_H__
#define __WINDOWHOOKER_H__
#include <Windows.h>
#include "HookDLL/HookDLL.h"
#pragma comment(lib, "Debug/HookDLL.lib")

namespace std { class thread; }
using Handler = void(*)(const MSG*);

class WindowHooker
{
public:
	WindowHooker();
	~WindowHooker();

	void BeginHooking(HWND hTargetWnd, Handler handler);
	void EndHooking();

private:
	void removeThread();
	static void threadFuntion(const WindowHooker& self);

private:
	std::thread* m_pThread;
	Handler m_Handler;
	HANDLE m_hPipe;
	HWND m_hTargetWnd;
	bool m_bFlag;
};

#endif

