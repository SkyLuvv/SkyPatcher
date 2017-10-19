
#include "Start.h"
#include "LocalCharacter.h"
#include "ReviveBox.h"
#include "AutoInput.h"
#include "Mods.h"
#include "FrameTimer.h"


LocalChara LChara;
ReviveBox RevBox;
DeadLock Deadlock;

using namespace std::chrono;
using namespace std::this_thread;

extern "C"
{
	uint32_t LCharaAddr = (uint32_t)&LChara;
	uint32_t RevBoxAddr = (uint32_t)&RevBox;
	uint32_t obj_DeadLockAddr = (uint32_t)&Deadlock;
}

void Sky::main()
{
	CreateMyConsole();

	CreateConnection();

	FreeConsole();

	AutoInput input;

	auto ModuleAddresses = Memory::GetAllModuleAddresses();

	LChara.Patch(ModuleAddresses);
	RevBox.Patch(ModuleAddresses);
	Deadlock.Patch(ModuleAddresses);

	while (true)
	{
		while (!LChara.GetHealth())
		{
			FrameTimer FT;
			RevBox.CreateReviveBox();

			while ((!LChara.GetHealth()))
			{
				input.Click(10);
				if (FT.TimePassed() > 0.2f)
					break;
				else if (GetAsyncKeyState(VK_ESCAPE))
					LChara.SetHealth(1.0f);
			}
		}
		sleep_for(milliseconds(10));
	}
	
}

void Sky::CreateMyConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

void Sky::CreateConnection()
{
	
	Client client("76.94.154.5", 1111);

	if (client.Connect() != 0)
	{
		std::cout << "Failed To Authentificate. Try Again." << std::endl;
		sleep_for(milliseconds(5000));
		exit(1);
	}

	std::cout << "SkyLuv's Patcher. Enjoy!" << std::endl << std::endl;
	std::cout << "Hit Escape When Dead To Stop Clicking." << std::endl;

	sleep_for(milliseconds(5000));
	
}

