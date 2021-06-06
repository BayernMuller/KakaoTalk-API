#pragma once
#include <Windows.h>

extern "C" __declspec(dllexport) void InstallHook(HWND hWnd);
extern "C" __declspec(dllexport) void UninstallHook();