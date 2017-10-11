
#include "Start.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Windows.h"


void Start::Start()
{
	typedef void(__thiscall * Func)(void* pThis, void* first, int32_t flag, void* third);

	Memory memory;

	CreateMyConsole();


	auto base = (uint32_t)(GetModuleHandle(0));

	auto functionaddr = (base + 0x10DEB0F);

	Rz_.returnaddr = (functionaddr + 0x05);


	//outputs the correct address which begins at the first element, but LEA doesn't
	std::cout << std::hex << &Rz_ << std::endl;

	std::cout << (int)offsetof(struct Rz, thirdarg);


	memory.WriteJump((char*)functionaddr,(uint32_t )&Rz::GrabArg );

	auto Func_ = (Func)(0x011BE4D0);

	auto * pThis = *(void**)0x0344EB08;
	
	while (true)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
		{
			Func_(pThis, (void*)(base + 0x2748e78), 5, (void*)Rz_.thirdarg);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
		
}

void Start::CreateMyConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

