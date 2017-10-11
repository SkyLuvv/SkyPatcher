#include "Start.h"
#include "Windows.h"


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


		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start::Start, 0, 0, 0 );
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
