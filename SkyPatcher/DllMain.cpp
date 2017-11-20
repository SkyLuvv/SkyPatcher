#include "MainWindow.h"
#include <optional>
#include <iostream>
#include <thread>
#include <chrono>
#include "Graphics.h"
#include "Game.h"
#include "Sky.h"

using namespace std::this_thread;
using namespace std::chrono;


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

	Sky sky;
	sky.Main(0);

	MainWindow window(hInstance);

	Graphics gfx(window.GetHWND(), window.Width, window.Height);

	Game game(gfx, window, sky);

	while (window.ProcessMessage())
	{
		gfx.BeginScene();

		game.Go();

		gfx.EndScene();
	}

}




