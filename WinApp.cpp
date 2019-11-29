#include "WinApp.h"
#include <cstring>
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

inline void WinApp::Assert(BOOL condition, wchar_t* msg)
{
	// A BOOL value with 0 indicates failure and success for value that does not equal to 0
	if (condition <= 0) MessageBox(NULL, msg, L"Error", MB_OK | MB_ICONWARNING);
}

inline void WinApp::Assert(HRESULT hr, wchar_t* msg)
{
	// An HRESULT value indicates success when it is >= 0, otherwise failure
	if (FAILED(hr)) MessageBox(NULL, msg, L"Error", MB_OK | MB_ICONWARNING);
}

inline void WinApp::AssertWndFuncs(HRESULT hr)
{
	// An HRESULT value indicates success when it is >= 0, otherwise failure
	if (FAILED(hr)) MessageBox(NULL, GetErrorMsg(GetLastError()).c_str(), L"Error", MB_OK | MB_ICONWARNING);
}

inline void WinApp::AssertWndFuncs(BOOL condition)
{
	// A BOOL value with 0 indicates failure and success for value that does not equal to 0
	if (condition <= 0) MessageBox(NULL, GetErrorMsg(GetLastError()).c_str(), L"Error", MB_OK | MB_ICONWARNING);
}

WinApp::WinApp(HINSTANCE hInstance, int nCmdShow) : WinApp()
{
	m_hInstance = hInstance;
	m_nCmdShow = nCmdShow;
}

int WinApp::InitInstance()
{
	AssertWndFuncs(RegisterWndClassEx());

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

	AssertWndFuncs(reinterpret_cast<BOOL>(m_hwnd));
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
	AssertWndFuncs(result);
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

std::wstring WinApp::GetErrorMsg(DWORD nErrorCode)
{
	// get language id
	DWORD value;
	int langResult = GetLocaleInfoEx(L"en-us", LOCALE_ILANGUAGE | LOCALE_RETURN_NUMBER, reinterpret_cast<LPWSTR>(&value), sizeof(DWORD) / sizeof(wchar_t));
	if (!langResult)
	{
		MessageBox(NULL, L"Unable to retreive language id", L"Error", MB_OK | MB_ICONERROR);
		return std::wstring();
	}
	LANGID langId = value;

	// get message corresponding its error code
	LPTSTR pBuffer = nullptr;
	DWORD formatResult = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,	// dwFlags
		NULL,																							// lpSource
		nErrorCode,																						// dwMessageId
		langId,																							// dwLanguageId
		reinterpret_cast<LPTSTR>(&pBuffer),																// lpBuffer
		0,																								// nSize
		NULL																							// pArgs
	);
	if (!formatResult)
	{
		MessageBox(NULL, L"Unable to retreive format message", L"Error", MB_OK | MB_ICONERROR);
		return std::wstring();
	}

	// store in an wstring instance and free buffer
	std::wstring msg = std::wstring(pBuffer, wcslen(pBuffer));
	LocalFree(pBuffer);
	return msg;
}
