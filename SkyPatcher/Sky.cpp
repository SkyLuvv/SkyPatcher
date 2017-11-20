
#include "Sky.h"
#include "FrameTimer.h"
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

Sky::Sky()

	:
	RevBox(std::make_unique<ReviveBox>()),
	DL(std::make_unique<DeadLock>()),
	LChara(std::make_unique<LocalChara>())
{

    modsmap =
	{
		{ modID::ReviveBox, reinterpret_cast<Mod*>(RevBox.get()) },
		{ modID::DeadLock,  reinterpret_cast<Mod*>(DL.get()) },
		{ modID::LocalChara,reinterpret_cast<Mod*>(LChara.get()) }
	};


	LCharaAddr = (uint32_t)((&LChara->datastart) + 1);
	RevBoxAddr = (uint32_t)((&RevBox->datastart) + 1);
	obj_DeadLockAddr = (uint32_t)((&DL->datastart) + 1);
}

void Sky::Main(HMODULE hModule)
{
	using namespace std;

	CreateConsole();

	cout << "                         SKY'S PATCHER, ENJOY!\n\n\n";

	cout << "KNOWN BUGS:\n\n";
	cout<<"1) Upon Normal Death (Not EvG Death) The Revive Menu Won't Show The Original Options. Toggle The Revive Mod Off To Allow Revival From That State.\n\n\n";


	for (auto & e : modsmap)
		e.second->Patch();

	CreateReviveThread();

	cin.get();

	FreeConsole();
}

void Sky::CreateConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

void Sky::CreateReviveThread()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AutoRevive, this, 0, 0);

	AutoReviveOn = true;
}

void AutoRevive(Sky * sky)
{
	AutoInput click(DIK_E, true);

	while (sky->AutoReviveOn)
	{
		if (!sky->LChara->GetHealth())
		{
			FrameTimer ft;

			while (!sky->LChara->GetHealth())
			{
				if (ft.TimePassed() >= sky->speed_RevBox)
				{
					sky->RevBox->CreateReviveBox();
					sky->RevBox->CreateReviveBox();

					sky->LChara->SetHealth(5.0f);
				}
				sleep_for(milliseconds(20));
			}
		}
		sleep_for(milliseconds(20));
	}
}
