#include "pch.h"
#include "HookDLL.h"

#pragma data_seg(".npdata")

HINSTANCE g_hModule = NULL;
HANDLE g_hPipe = NULL;
HHOOK g_hHook = NULL;

#pragma data_seg()
#pragma comment (linker, "/SECTION:.npdata,RWS")

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        DWORD dwWritten;
        MSG* pMsg = reinterpret_cast<LPMSG>(lParam);
        WriteFile(g_hPipe, pMsg, sizeof(MSG), &dwWritten, NULL);
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) bool InstallHook(HWND hTargetWnd)
{
    if (g_hHook || g_hPipe)
        return false;

    DWORD pid, tid;
    tid = GetWindowThreadProcessId(hTargetWnd, &pid);

    g_hPipe = CreateFile(PIPE_NAME, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (g_hPipe == INVALID_HANDLE_VALUE)
    {
        g_hPipe = NULL;
        return false;
    }
    g_hHook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, g_hModule, tid);
    return true;
}

extern "C" __declspec(dllexport) void UninstallHook()
{
    CloseHandle(g_hPipe);
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

