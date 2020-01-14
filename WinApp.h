#pragma once
#include <Windows.h>
#include <string>
class WinApp
{
private:
	HWND m_hwnd;
	HINSTANCE m_hInstance;
	WNDCLASSEX m_wc;
	int m_nCmdShow;
	std::wstring m_sTitle;
	std::wstring m_sClassName;

private:
	static LRESULT CALLBACK SetupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WinApp() : m_hwnd(NULL), m_hInstance(NULL), m_wc(), m_nCmdShow(NULL), m_sTitle(L"Desktop Application"), m_sClassName(L"DesktopClass") {}
	ATOM RegisterWndClassEx();

public:
	WinApp(HINSTANCE hInstance, int nCmdShow);
	~WinApp() {}
	int InitInstance();
	int Run();
	int ExitInstance();

};

