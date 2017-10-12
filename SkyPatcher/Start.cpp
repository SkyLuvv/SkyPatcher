
#include "Start.h"


void Sky::main()
{
	CreateMyConsole();

	auto ModuleAddresses = Memory::GetAllModuleAddresses();

	if (!(LChara.Patch(ModuleAddresses)))
		std::cout << "Patch Failed : LChara.Patch_GetBase" << std::endl;



	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 1)
		{
			std::cout << " Health Address : " << std::hex << LChara.addr_base + LChara.off_health << std::endl;
		}

		Sleep(1000);
	}
}

void Sky::CreateMyConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

