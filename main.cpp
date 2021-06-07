#include <iostream>
#include <vector>

#include "WindowFinder.h"
#include "WindowHooker.h"

using namespace std;

int main()
{
	HWND hKakao = WindowFinder::FindWindowByName(L"Ä«Ä«¿ÀÅå");
	wchar_t str[MAX_SIZE];
	WindowFinder::GetWindowClass(str, hKakao, MAX_SIZE);
	wcout << str << endl;
	if (hKakao)
	{
		InstallHook(hKakao);
		
		cin.get();
		UninstallHook();
	}
}