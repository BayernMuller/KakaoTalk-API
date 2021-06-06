#include <iostream>
#include <vector>
#include "HookDLL/HookDLL.h"
#include "WindowFinder.h"
#pragma comment(lib, "Debug/HookDLL.lib")

using namespace std;

void callback(long param)
{
	cout << "-" << endl;
}

int main()
{
	HWND hKakao = WindowFinder::FindWindowByName(L"Ä«Ä«¿ÀÅå");
	wchar_t str[MAX_SIZE];
	WindowFinder::GetWindowClass(str, hKakao, MAX_SIZE);
	wcout << str << endl;
	if (hKakao)
	{
		InstallHook(hKakao);
		tuple<int,int>
		cin.get();
		UninstallHook();
	}
}