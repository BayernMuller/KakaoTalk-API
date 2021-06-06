
#include "HookDLL.h"
#include "pch.h"

#pragma data_seg(".npdata")

HINSTANCE g_hModule = NULL;
HHOOK g_hHook = NULL;

#pragma data_seg()
#pragma comment (linker, "/SECTION:.npdata,RWS")
#pragma warning(disable:4996)

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) void InstallHook(HWND hWnd)
{
    DWORD pid, tid;
    tid = GetWindowThreadProcessId(hWnd, &pid);
    g_hHook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, g_hModule, tid);
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

