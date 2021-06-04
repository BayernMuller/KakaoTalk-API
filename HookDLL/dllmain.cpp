#include "dllmain.h"
#include "pch.h"

#pragma data_seg(".npdata")
HINSTANCE g_hModule = NULL;
HHOOK g_hHook = NULL;
void (*g_fpCallback)(LPARAM lParam);
#pragma data_seg()
#pragma comment (linker, "/SECTION:.npdata,RWS")

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && g_fpCallback)
    {
        g_fpCallback(lParam);
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) void InstallHook(HWND hWnd, void(*fpCallback)(long))
{
    DWORD pid, tid;
    tid = GetWindowThreadProcessId(hWnd, &pid);
    g_hHook = SetWindowsHookEx(WH_CALLWNDPROCRET, HookProc, g_hModule, tid);
    g_fpCallback = fpCallback;
}

extern "C" __declspec(dllexport) void UninstallHook()
{
    UnhookWindowsHookEx(g_hHook);
}

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID lpRes)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hModule = hInst;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

