#ifndef __WINDOWFINDER_H__
#define __WINDOWFINDER_H__
#include <Windows.h>

// Forward declaration for STL
namespace std 
{
	template<class _Ty> class allocator;
	template<class _Ty, class _Ax = allocator<_Ty>> class vector;
	template<class _Ty, class _Ax = allocator<_Ty>> class list;
	template<class _Ty, class _Ax = allocator<_Ty>> class set;	
}

using HandleArray = std::vector<HWND>;
using HandleList = std::list<HWND>;
using HandleSet = std::set<HWND>;
constexpr int MAX_SIZE = 256;

class WindowFinder
{
public:
	template<class Container>
	static bool FindParentWindows(Container& set);

	template<class Container>
	static bool FindParentWindows(WNDENUMPROC lpEnumFunc, Container& set);

	template<class Container>
	static bool FindChildWindows(HWND hParent, Container& set);

	template<class Container>
	static bool FindChildWindows(HWND hParent, WNDENUMPROC lpEnumFunc, Container& set);


	static HWND FindWindowByName(const wchar_t str[]);
	static HWND FindWindowByClass(const wchar_t str[]);
	static HWND FindChildBySubString(HWND hParent, const wchar_t* str);

	static wchar_t* GetWindowName(wchar_t str[], HWND hWnd, int maxsize);
	static wchar_t* GetWindowClass(wchar_t str[], HWND hWnd, int maxsize);

protected:
	template<class Container>
	static BOOL __stdcall parentWindowsFilter(HWND hWnd, LPARAM lParam);

	template<class Container>
	static BOOL __stdcall childWindowsFilter(HWND hWnd, LPARAM lParam);

private:

};


template<class Container>
inline static bool WindowFinder::FindParentWindows(Container& set)
{
	return EnumWindows(parentWindowsFilter<Container>, LPARAM(&set));
}

template<class Container>
inline static bool WindowFinder::FindParentWindows(WNDENUMPROC lpEnumFunc, Container& set)
{
	return EnumWindows(lpEnumFunc, LPARAM(&set));
}

template<class Container>
inline static bool WindowFinder::FindChildWindows(HWND hParent, Container& set)
{
	return EnumChildWindows(hParent, childWindowsFilter<Container>, LPARAM(&set));
}

template<class Container>
inline static bool WindowFinder::FindChildWindows(HWND hParent, WNDENUMPROC lpEnumFunc, Container& set)
{
	return EnumChildWindows(hParent, lpEnumFunc, LPARAM(&set));
}

template<class Container>
static BOOL __stdcall WindowFinder::parentWindowsFilter(HWND hWnd, LPARAM lParam)
{
	auto* handles = reinterpret_cast<Container*>(lParam);
	if (hWnd)
	{
		if (!::IsWindowVisible(hWnd))
			return TRUE;
		if (::GetWindowTextLength(hWnd) == 0)
			return TRUE;
		if (::GetParent(hWnd) != 0)
			return TRUE;
		handles->push_back(hWnd);
		return TRUE;
	}
	return FALSE;
}

template<class Container>
static BOOL __stdcall WindowFinder::childWindowsFilter(HWND hWnd, LPARAM lParam)
{
	auto* handles = reinterpret_cast<Container*>(lParam);
	if (hWnd)
	{
		handles->push_back(hWnd);
		return TRUE;
	}
	return FALSE;
}

#endif