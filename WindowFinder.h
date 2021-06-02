#ifndef __WINDOWFINDER_H__
#define __WINDOWFINDER_H__
#include <Windows.h>

class WindowFinder
{
public:
	template<class Container>
	static bool FindAllWindows(Container& set)
	{
		return EnumWindows(&WindowFinder::getWindowsList<Container>, LPARAM(&set));
	}

	template<class Container>
	static bool FindAllWindows(WNDENUMPROC lpEnumFunc, Container& set)
	{
		return EnumWindows(lpEnumFunc, LPARAM(&set));
	}

	template<class Container>
	static WNDENUMPROC GetCallbackFunc()
	{
		return getWindowsList<Container>;
	}

	static HWND FindWindowByCaption(const wchar_t[]);
	static HWND FindWindowByClass(const wchar_t[]);
	static wchar_t* GetWindowName(wchar_t[], HWND, int);
	static wchar_t* GetWindowClass(wchar_t[], HWND, int);

private:
	template<class Container>
	static BOOL __stdcall getWindowsList(HWND hWnd, LPARAM lParam)
	{
		auto* con = reinterpret_cast<Container*>(lParam);
		if (hWnd)
		{
			if (!::IsWindowVisible(hWnd))
				return TRUE;
			if (::GetWindowTextLength(hWnd) == 0)
				return TRUE;
			if (::GetParent(hWnd) != 0)
				return TRUE;
			con->push_back(hWnd);
			return TRUE;
		}
		return FALSE;
	}
};

#endif