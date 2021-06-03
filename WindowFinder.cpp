#include "WindowFinder.h"

HWND WindowFinder::FindWindowByName(const wchar_t name[])
{
	return ::FindWindow(NULL, name);
}

HWND WindowFinder::FindWindowByClass(const wchar_t class_[])
{
	return ::FindWindow(class_, NULL);
}

wchar_t* WindowFinder::GetWindowName(wchar_t str[], HWND hWnd, int maxsize)
{
	if (!::IsWindow(hWnd))
		return nullptr;
	::GetWindowText(hWnd, str, maxsize);
	return str;
}

wchar_t* WindowFinder::GetWindowClass(wchar_t str[], HWND hWnd, int maxsize)
{
	if (!::IsWindow(hWnd))
		return nullptr;
	::GetClassName(hWnd, str, maxsize);
	return str;

}