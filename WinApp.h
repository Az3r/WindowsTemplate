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
	ATOM RegisterWndClassEx();
protected:
	virtual LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int InitInstance();
	virtual int Run();
	virtual int ExitInstance();
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


	inline std::wstring GetTitle() const noexcept { return mTitle; }
	inline int GetWidth() const noexcept { return mWidth; }
	inline int GetHeight() const noexcept { return mHeight; }
	RECT GetPosition() const noexcept { return { mLeft, mTop, mWidth - mLeft - 1, mHeight - mTop - 1 }; }
	
	void SetTitle(std::wstring title) noexcept;
	void Move(int width, int height, int x, int y);
	inline void SetPosition(int x, int y) { Move(mWidth, mHeight, x, y); }
	inline void SetSize(int width, int height) { Move(width, height, mLeft, mTop); }

	virtual int Start();


};

extern HINSTANCE g_hInstance;
extern int g_nCmdShow;
