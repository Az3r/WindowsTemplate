#include "WinApp.h"
#include "Exception.h"


HINSTANCE g_hInstance;
int g_nCmdShow;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;


	WinApp theApp;
	int result;
	if ((result = theApp.InitInstance()) < 0) return result;
	theApp.Run();
	if ((result = theApp.ExitInstance()) < 0) return result;


	return 0;
}