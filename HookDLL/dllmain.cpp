#include "pch.h"
#include "HookDLL.h"
#include <map>

#pragma data_seg(".npdata")

HINSTANCE g_hModule = NULL;
std::map<HWND, std::pair<HANDLE, HHOOK>> g_Hookers;

#pragma data_seg()
#pragma comment (linker, "/SECTION:.npdata,RWS")

static constexpr int MAX_SIZE = 256;

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MSG* pMsg = reinterpret_cast<LPMSG>(lParam);
    if (nCode >= 0)
    {
        DWORD dwWritten;
        WriteFile(g_Hookers[pMsg->hwnd].first, pMsg, sizeof(MSG), &dwWritten, NULL);
    }
    return CallNextHookEx(g_Hookers[pMsg->hwnd].second, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) wchar_t* GetPipeName(HWND hWnd, wchar_t buf[])
{
    
    lstrcpy(buf, L"\\\\.\\pipe\\");
    GetWindowText(hWnd, buf + lstrlen(buf), MAX_SIZE);
    GetClassName(hWnd, buf + lstrlen(buf), MAX_SIZE);
    return buf;
}

extern "C" __declspec(dllexport) bool InstallHook(HWND hTargetWnd)
{
    DWORD pid, tid;
    tid = GetWindowThreadProcessId(hTargetWnd, &pid);
    
    wchar_t pipeName[MAX_SIZE] = { 0 };
    GetPipeName(hTargetWnd, pipeName);
    
    HANDLE hPipe = CreateFile(pipeName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe == INVALID_HANDLE_VALUE)
        return false;

    HHOOK hHook = SetWindowsHookEx(WH_GETMESSAGE, HookProc, g_hModule, tid);
    g_Hookers[hTargetWnd] = std::make_pair(hPipe, hHook);
    return true;
}

extern "C" __declspec(dllexport) void UninstallHook(HWND hTargetWnd)
{
    CloseHandle(g_Hookers[hTargetWnd].first);
    UnhookWindowsHookEx(g_Hookers[hTargetWnd].second);
    g_Hookers.erase(hTargetWnd);
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

