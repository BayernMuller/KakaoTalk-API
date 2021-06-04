#include "WindowFinder.h"
#include <utility>

HWND WindowFinder::FindWindowByName(const wchar_t name[])
{
	return ::FindWindow(NULL, name);
}

HWND WindowFinder::FindWindowByClass(const wchar_t class_[])
{
	return ::FindWindow(class_, NULL);
}

HWND WindowFinder::FindChildBySubString(HWND hParent, const wchar_t* str)
{
	auto param = std::make_pair(HWND(), str);
	WNDENUMPROC proc = [](HWND hWnd, LPARAM lParam) -> BOOL 
	{
		auto& args = *reinterpret_cast<decltype(param)*>(lParam);
		if (hWnd)
		{
			wchar_t name[MAX_SIZE];
			GetWindowName(name, hWnd, MAX_SIZE);
			if (*name && wcsstr(name, args.second))
			{
				args.first = hWnd;
				return FALSE;
			}
			return TRUE;
		}
		return FALSE;
	};
	EnumChildWindows(hParent, proc, reinterpret_cast<LPARAM>(&param));
	return param.first;
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