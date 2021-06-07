#pragma once
#include <Windows.h>

constexpr wchar_t PIPE_NAME[] = L"HookPipe";

extern "C" __declspec(dllexport) bool InstallHook(HWND hTargetWnd);
extern "C" __declspec(dllexport) void UninstallHook();