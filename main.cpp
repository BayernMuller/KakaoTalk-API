#include <iostream>
#include <vector>

#include "WindowFinder.h"
#include "WindowHooker.h"

using namespace std;

void callback(const MSG* pMsg)
{
	cout << pMsg->message << endl;
}

int main()
{
	HWND hKakao = WindowFinder::FindWindowByName(L"Ä«Ä«¿ÀÅå");
	
	WindowHooker hook;
	hook.BeginHooking(hKakao, callback);
	cin.get();
	hook.EndHooking();
}