#include "Start.h"
#include "Windows.h"
#include "MyWindow.h"
#include "Interface.h"

HMODULE theModule;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);

BOOLEAN WINAPI  DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//for better performance reasons
	    DisableThreadLibraryCalls(hModule);

		theModule = hModule;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)wWinMain, 0, 0, 0 );
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Sky::main(theModule);

	Interface interface(hInstance);
	
	while (interface.ProcessMessage())
	{
		
	}
}

