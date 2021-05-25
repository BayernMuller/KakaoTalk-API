#include <iostream>
#include "WindowFinder.h"
#include <list>
#include <vector>
using namespace std;

int main()
{
	list<HWND> lis;
	WindowFinder::Find(lis);

	vector<HWND> vec;
	WindowFinder::Find(vec);

	wcout.imbue(locale("kor"));
	wchar_t str[256] = { 0 };
	for (auto i : vec)
	{
		WindowFinder::GetWindowName(str, i, 256);
		wcout << str << endl;
	}
	cout << "\n\n";
	for (auto i : lis)
	{
		WindowFinder::GetWindowClass(str, i, 256);
		wcout << str << endl;
	}
}