#include <iostream>
#include <vector>
#include "WindowFinder.h"
using namespace std;

int main()
{
	HWND hKakao = WindowFinder::FindWindowByName(L"Ä«Ä«¿ÀÅå");
	if (hKakao)
	{
		HWND handle = WindowFinder::FindChildBySubString(hKakao, L"ListCtrl");
		HandleArray arr;
		WindowFinder::FindChildWindows(handle, arr);

		for (auto child : arr)
		{
			wchar_t str[256] = { 0, };
			WindowFinder::GetWindowClass(str, child, 256);
			wcout << str << endl;
			WindowFinder::GetWindowName(str, child, 256);
			wcout << str << endl;
			

			DWORD pid, tid;
			tid = GetWindowThreadProcessId(child, &pid);
			cout << (void*)pid << endl << (void*)tid << endl;
			cout << "----" << endl;
		}
		return 0;
	}
	cout << "hKakao is NULL" << endl;
}