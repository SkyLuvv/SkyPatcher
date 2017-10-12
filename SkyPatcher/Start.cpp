
#include "Start.h"


void Sky::main()
{
	CreateMyConsole();

	auto ModuleAddresses = Memory::GetAllModuleAddresses();

	LChara.Patch(ModuleAddresses);

	RevBox.Patch(ModuleAddresses);

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 1)
		{
			RevBox.CreateReviveBox();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Sky::CreateMyConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

