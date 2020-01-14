#include "WinApp.h"
#include "Exception.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try
	{
		throw_exception("Hello");
	}
	catch (const Exception& e)
	{
		MessageBoxA(NULL, e.what(), e.name().c_str(), NULL);
	}


	WinApp theApp(hInstance, nCmdShow);
	int result;
	if ((result = theApp.InitInstance()) < 0) return result;
	theApp.Run();
	if ((result = theApp.ExitInstance()) < 0) return result;

	return 0;
}