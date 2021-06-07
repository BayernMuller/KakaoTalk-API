#include "WindowHooker.h"
#include <thread>

WindowHooker::WindowHooker()
	: m_Handler(nullptr)
	, m_pThread(nullptr)
	, m_hTargetWnd(nullptr)
	, m_hPipe(nullptr)
	, m_bFlag(false)
{
}

WindowHooker::~WindowHooker()
{
	EndHooking();
}

void WindowHooker::BeginHooking(HWND hTargetWnd, Handler handler)
{
	if (m_pThread)
		return;
	wchar_t pipeName[256];
	GetPipeName(hTargetWnd, pipeName);

	m_hPipe = CreateNamedPipe(pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		1,
		1024 * 16,
		1024 * 16,
		1000,
		NULL);

	m_bFlag = true;
	m_Handler = handler;
	m_hTargetWnd = hTargetWnd;
	m_pThread = new std::thread(threadFuntion, *this);
	InstallHook(hTargetWnd);
}

void WindowHooker::EndHooking()
{
	if (m_hTargetWnd)
		UninstallHook(m_hTargetWnd);
	if (m_hPipe)
		DisconnectNamedPipe(m_hPipe);
	removeThread();	
	m_hTargetWnd = nullptr;
	m_Handler = nullptr;
}

void WindowHooker::removeThread()
{
	if (m_pThread)
	{
		m_bFlag = false;
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}
}
#include <iostream>
void WindowHooker::threadFuntion(const WindowHooker& self)
{
	std::cout << "begin" << std::endl;
	while (!ConnectNamedPipe(self.m_hPipe, NULL))   // wait for someone to connect to the pipe
	{
		MSG msg;
		DWORD dwRead;
		while (ReadFile(self.m_hPipe, &msg, sizeof(MSG), &dwRead, NULL) != 0)
		{
			self.m_Handler(&msg);
		}
		std::cout << "dd" << std::endl;
	}
	std::cout << "end" << std::endl;
}
