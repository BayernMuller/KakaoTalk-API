#pragma once

struct HWND;


extern "C" __declspec(dllimport) void InstallHook(HWND hWnd, void(*fpCallback)(long));
extern "C" __declspec(dllimport) void UninstallHook();