#pragma once
#include <Windows.h>


extern "C" __declspec(dllexport) wchar_t* GetPipeName(HWND hWnd, wchar_t buf[]);
extern "C" __declspec(dllexport) bool InstallHook(HWND hTargetWnd);
extern "C" __declspec(dllexport) void UninstallHook(HWND hTargetWnd);