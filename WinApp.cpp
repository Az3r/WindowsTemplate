#include "WinApp.h"
#include "Exception.h"

LRESULT WinApp::SetupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WinApp* lpWinApp = nullptr;
	if (msg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		lpWinApp = static_cast<WinApp*> (lpcs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(lpWinApp));
	}
	else lpWinApp = reinterpret_cast<WinApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (lpWinApp) return lpWinApp->WndProc(hwnd, msg, wParam, lParam);
	else return DefWindowProc(hwnd, msg, wParam, lParam);
}
ATOM WinApp::RegisterWndClassEx()
{
	ZeroMemory(&m_wc, sizeof(m_wc));

	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.hInstance = m_hInstance;
	m_wc.lpfnWndProc = WinApp::SetupWndProc;
	m_wc.lpszClassName = m_sClassName.c_str();

	return RegisterClassEx(&m_wc);
}


WinApp::WinApp(HINSTANCE hInstance, int nCmdShow) : WinApp()
{
	m_hInstance = hInstance;
	m_nCmdShow = nCmdShow;
}

int WinApp::InitInstance()
{
	m_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		m_sClassName.c_str(),
		m_sTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		m_hInstance,
		this
	);

	Exception::throw_if_false((BOOL)m_hwnd, Exception::TranslateErrorCode(GetLastError()), __LINE__, "Window Creation Failure");

	ShowWindow(m_hwnd, m_nCmdShow);
	UpdateWindow(m_hwnd);

	return 0;
}

int WinApp::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	BOOL result;

	while (result = GetMessage(&msg, m_hwnd, NULL, NULL))
	{
		if (result < 0)
		{
			// window has been closed and destroyed
			return 0;
		}
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}

int WinApp::ExitInstance()
{
	BOOL result = UnregisterClass(m_sClassName.c_str(), m_hInstance);
	Exception::throw_if_false(result, Exception::TranslateErrorCode(GetLastError()), __LINE__, "Unregisteration Failure");
	return 0;
}

LRESULT WinApp::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT painter;
		HDC hdc = BeginPaint(hwnd, &painter);

		RECT rect;
		GetClientRect(hwnd, &rect);

		FillRect(hdc, &rect, CreateSolidBrush(RGB(0x69, 0x69, 0x69)));

		EndPaint(hwnd, &painter);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
