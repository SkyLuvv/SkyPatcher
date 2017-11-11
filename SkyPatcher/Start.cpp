
#include "Start.h"
#include "FrameTimer.h"
#include "Winsock.h"
#include "DirectInputDefines.h"
#include "AutoInput.h"


using namespace std::chrono;
using namespace std::this_thread;

extern "C"
{
	uint32_t LCharaAddr;
	uint32_t RevBoxAddr;
	uint32_t obj_DeadLockAddr;
}


void Sky::main(HMODULE hModule)
{
	CreateMyConsole();

	std::cout << "Imagine's Patcher. Enjoy!" << std::endl << std::endl;

	Init();
	ApplyPatches();

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Sky::ReviveThread, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Sky::BotThread, 0, 0, 0);

	sleep_for(milliseconds(10000));

	FreeConsole();
	

}

void Sky::Init()
{
	Mods.push_back(std::make_unique<DeadLock>());
	Mods.push_back(std::make_unique<ReviveBox>());
	Mods.push_back(std::make_unique<LocalChara>());



	obj_DeadLockAddr = (uint32_t)&(*Mods[(size_t)Mod::ID::DeadLock]);
	RevBoxAddr = (uint32_t)&(*Mods[(size_t)Mod::ID::ReviveBox]);
	LCharaAddr = (uint32_t)&(*Mods[(size_t)Mod::ID::LocalChara]);
    
}

void Sky::CreateMyConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

bool Sky::CreateConnection()
{
	Client client("76.94.154.5", 1111);

	if (client.Connect() == 0)
		return true;
	else
		return false;
}

void Sky::ReviveThread()
{
	std::cout << "ReviveBox Thread Created. \n\n";

	auto  RevBox = *(ReviveBox*)&Mods[(size_t)Mod::ID::ReviveBox];
	auto LChara = *(LocalChara*)&Mods[(size_t)Mod::ID::LocalChara];

	while (true)
	{
	
		while (!LChara.GetHealth())
		{
			FrameTimer FT;

			while (!LChara.GetHealth())
			{
				if (FT.TimePassed() > speed_RevBox)
				{
					RevBox.CreateReviveBox();;
					RevBox.CreateReviveBox();;
					LChara.SetHealth(5.0f);
					break;
				}
				sleep_for(milliseconds(10));
			}
		}
		sleep_for(milliseconds(20));
	}

}

void Sky::BotThread()
{
	AutoInput input(DIK_E, true);

	std::cout << "EBOT Thread Created." << std::endl;
	std::cout << "Hold 'X' to use EBOT. \n\n";

	while (true)
	{
		if (GetAsyncKeyState('X'))
			input.Hit(speed_EBOT);
		else
			sleep_for(milliseconds(50));
	}
}

void Sky::ApplyPatches()
{
	for (auto i = 0; i < Mods.size(); ++i)
		Mods[i]->Patch();
}

