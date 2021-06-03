#include <iostream>
#include <vector>
#include "WindowFinder.h"
using namespace std;

int main()
{
	HandleArray arr;
	WindowFinder::FindParentWindows(arr);
	wcout.imbue(locale("kor"));
	for (auto i : arr)
	{
		wchar_t str[256];
		cout << i << endl;
		WindowFinder::GetWindowName(str, i, 256);
		wcout << str << endl;
		WindowFinder::GetWindowClass(str, i, 256);
		wcout << str << endl << endl;
	}
}