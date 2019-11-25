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
	WinApp() : m_hwnd(NULL), m_hInstance(NULL), m_wc(), m_nCmdShow(NULL), m_sTitle(L"Desktop Application"), m_sClassName(L"DesktopClass") {}
	ATOM RegisterWndClassEx();
public:
	WinApp(HINSTANCE hInstance, int nCmdShow);
	~WinApp() {}
	int InitInstance();
	int Run();
	int ExitInstance();
	static LRESULT CALLBACK WndProcDummy(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static std::wstring GetErrorMsg(DWORD nErrorCode);
	static void Assert(BOOL condition, wchar_t* msg);
	static void Assert(HRESULT hr, wchar_t* msg);

	// Asserts Windows API methods' result with error code returned from GetLastError()
	static void AssertWndFuncs(HRESULT hr);
	static void AssertWndFuncs(BOOL condition);
};

