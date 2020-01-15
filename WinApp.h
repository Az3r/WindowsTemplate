#pragma once
#include <Windows.h>
#include <string>
class WinApp
{
private:
	HWND mHWND;
	WNDCLASSEX mWC;
	std::wstring mTitle;
	int mWidth, mHeight, mLeft, mTop;
	static std::wstring sClassName;

private:
	static LRESULT CALLBACK SetupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	ATOM RegisterWndClassEx();

public:
	WinApp() : mHWND(NULL), mWC(), 
		mTitle(L"Desktop Application"),
		mWidth(CW_USEDEFAULT), mHeight(CW_USEDEFAULT), mLeft(CW_USEDEFAULT), mTop(CW_USEDEFAULT)

	{}
	WinApp(std::wstring title) noexcept;
	WinApp(std::wstring title, int width, int height) noexcept;
	WinApp(std::wstring title, int width, int height, int x, int y) noexcept;
	WinApp(int width, int height) noexcept;
	WinApp(int width, int height, int x, int y) noexcept;

	WinApp(const WinApp&) = delete;
	WinApp& operator=(const WinApp&) = delete;
	~WinApp() noexcept {}



	int InitInstance();
	int Run();
	int ExitInstance();

};

extern HINSTANCE g_hInstance;
extern int g_nCmdShow;
