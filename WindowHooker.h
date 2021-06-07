#ifndef __WINDOWHOOKER_H__
#define __WINDOWHOOKER_H__
#include <thread>
#include <Windows.h>
#include "HookDLL/HookDLL.h"
#pragma comment(lib, "Debug/HookDLL.lib")

using Handler = void(*)(MSG* pMsg);

class WindowHooker
{
public:
	WindowHooker();
	~WindowHooker();

	void SetHandler(Handler handler);
	void BeginHooking(HWND hTargetWnd);
	void EndHooking();
	
private:
	std::thread* mpThread;
	Handler mHandler;
	HWND mhTargetWnd;

private:
	static int mObjectCount;
};

#endif

