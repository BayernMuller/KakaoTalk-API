#include "WindowHooker.h"

WindowHooker::WindowHooker()
	: mHandler(nullptr), mpThread(nullptr), mhTargetWnd(nullptr)
{
	if (mObjectCount > 0)
		throw std::exception("WindowHooker class' instance must be only one");
	mObjectCount++;
}

WindowHooker::~WindowHooker()
{
	mObjectCount--;
}

void WindowHooker::SetHandler(Handler handler)
{
}

void WindowHooker::BeginHooking(HWND hTargetWnd)
{
}

void WindowHooker::EndHooking()
{
}
