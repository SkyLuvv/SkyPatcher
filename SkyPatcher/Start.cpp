
#include "Start.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Windows.h"




INPUT click;


Memory memory;


namespace Rez
{

	uint32_t firstarg = 0;
	uint32_t secondarg = 5;
	uint32_t *  thirdarg = nullptr;
	uint32_t    returnaddr = 0;
	void * pThis = *(void**)0x0344EB08;
	uint32_t addr_func = 0x011BE4D0;

	typedef void(__thiscall * Func)(void* pThis, void* first, int32_t flag, void* third);
	Func Func_ = (Func)addr_func;

	uint32_t off_funcgrabargs = 0x10DEB0F;
	uint32_t off_firstarg = 0x2748e78;
	
	void  GrabArg();

};

namespace LocalChara
{
	uint32_t off_health = 0x134;
	uint32_t addr_base = 0;
	uint32_t off_func = 0x6D49D0;
	uint32_t returnaddr = 0;
	void GrabBase();
}

void __declspec(naked) Rez::GrabArg()
{

	__asm
	{
	
		/*
		cmp dead, 0
		je original
		
		push edx
		push ecx
		push edi
		push esi
		push eax

		mov ecx, [pThis]
		//get the third arg
		mov eax, dword ptr[ebp - 0x34]

		push eax
		push secondarg

		push firstarg

		mov dead, 0

		call [addr_func]

		popall:
		pop eax
		pop esi
		pop edi
		pop ecx
		pop edx
		*/


		//original:
		push eax
		mov eax, dword ptr[ebp - 0x34]

		mov thirdarg , eax

		pop eax

		call edx
		sub eax, 0x00

		jmp[returnaddr]

	}

}

void __declspec(naked) LocalChara::GrabBase()
{
	__asm
	{
		mov addr_base, ecx 
							
	    mov ax, [ecx + 0x000001C4]
	    jmp [returnaddr]
	}
}

void Start::Start()
{
	click.type = INPUT_MOUSE;

	CreateMyConsole();

	auto base = (uint32_t)(GetModuleHandle(0));

	Setup_ReviveBoxInf(base);
	Setup_LocalCharaInf(base);

	while (true)
	{

		if (LocalChara::addr_base != 0)
		{
			std::cout << "address of health: " << LocalChara::addr_base + LocalChara::off_health << std::endl;
			while (true)
			{

				if (*(float*)(LocalChara::addr_base + LocalChara::off_health) == 0)
				{
					if (*Rez::thirdarg > 0)
					{
						Rez::Func_(Rez::pThis, (void*)(base + Rez::off_firstarg), 5, (void*)Rez::thirdarg);
					}
				

					while (*(float*)(LocalChara::addr_base + LocalChara::off_health) == 0)
					{
						
						click.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
						
						SendInput(1, &click, sizeof(INPUT));

						click.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);

						SendInput(1, &click, sizeof(INPUT));

						std::this_thread::sleep_for(std::chrono::milliseconds(30));
					}

				}

				else if (GetAsyncKeyState(VK_DOWN))
				{
					if (*Rez::thirdarg > 0)
					{
						if ((*(float*)(LocalChara::addr_base + LocalChara::off_health) <= 0) && *Rez::thirdarg > 0)
						{
							Rez::Func_(Rez::pThis, (void*)(base + Rez::off_firstarg), 5, (void*)Rez::thirdarg);
							std::this_thread::sleep_for(std::chrono::milliseconds(40));
						}
					}
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(40));
				}
			}
		

		}
		std::cout << &LocalChara::addr_base << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
	}
	
		
}

void Start::Setup_ReviveBoxInf(const uint32_t & ModuleBase)
{
	auto grabargs_functionaddr = (ModuleBase + Rez::off_funcgrabargs);

	Rez::firstarg = (ModuleBase + Rez::off_firstarg);

	Rez::returnaddr = (grabargs_functionaddr + 0x05);

	memory.WriteJump((char*)grabargs_functionaddr, (uint32_t)Rez::GrabArg);

}

void Start::Setup_LocalCharaInf(const uint32_t & ModuleBase)
{
	auto funcaddress = (ModuleBase + LocalChara::off_func);

	LocalChara::returnaddr = (funcaddress + 0x07);

	memory.WriteJump((char*)funcaddress, (uint32_t)LocalChara::GrabBase);

}

void Start::CreateMyConsole()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}
