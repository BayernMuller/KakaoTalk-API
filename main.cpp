#include <iostream>
#include <vector>
#include "WindowFinder.h"
using namespace std;

int main()
{
	HWND hKakao = WindowFinder::FindWindowByName(L"Ä«Ä«¿ÀÅå");
	if (hKakao)
	{
		HandleArray arr;
		WindowFinder::FindChildWindows(hKakao, arr);

		for (const auto& handle : arr)
		{
			wchar_t str[256] = { 0, };
			WindowFinder::GetWindowClass(str, handle, 256);
			wcout << str << endl;
			WindowFinder::GetWindowName(str, handle, 256);
			wcout << str << endl;
			

			DWORD pid, tid;
			tid = GetWindowThreadProcessId(handle, &pid);
			cout << (void*)pid << endl << (void*)tid << endl;
			cout << "---------" << endl;
		}
		return 0;
	}
	cout << "hKakao is NULL" << endl;
}