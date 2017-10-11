
#include "Start.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Windows.h"

Memory memory;

namespace Rez
{
	typedef void(__thiscall * Func)(void* pThis, void* first, int32_t flag, void* third);

	uint32_t addr_func = 0x011BE4D0;
	Func Func_ = (Func)addr_func;
	uint32_t off_funcgrabargs = 0x10DEB0F;
	uint32_t off_firstarg = 0x2748e78;
	void * pThis = *(void**)0x0344EB08;
	uint32_t *  ReviveBox_thirdarg;
	uint32_t    ReviveBox_returnaddr;
	void  ReviveBox_GrabArg();

};



namespace LocalChara
{
	uint32_t addr_base = 0;
	uint32_t off_health = 0x140;
	uint32_t off_func = 0x645B80;
	uint32_t returnaddr = 0;
	void GrabBase();
}

void __declspec(naked) Rez::ReviveBox_GrabArg()
{

	__asm
	{
		push ecx
		push eax

		//get the third argument for the box function from here
		mov eax, [ebp - 0x34]
		mov ReviveBox_thirdarg, eax

		pop eax
		pop ecx

		call edx
		sub eax, 0x00

		jmp[ReviveBox_returnaddr]
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

	CreateMyConsole();

	auto base = (uint32_t)(GetModuleHandle(0));

	Setup_ReviveBoxInf(base);
	Setup_LocalCharaInf(base);

	
	while (true)
	{
	
		if (*(float*)(LocalChara::addr_base + LocalChara::off_health) == 0)
		{
			Rez::Func_(Rez::pThis, (void*)(base + Rez::off_firstarg), 5, (void*)Rez::ReviveBox_thirdarg);
		}
		else 

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
		
}

void Start::Setup_ReviveBoxInf(const uint32_t & ModuleBase)
{
	auto grabargs_functionaddr = (ModuleBase + Rez::off_funcgrabargs);

	Rez::ReviveBox_returnaddr = (grabargs_functionaddr + 0x05);

	memory.WriteJump((char*)grabargs_functionaddr, (uint32_t)Rez::ReviveBox_GrabArg);

}

void Start::Setup_LocalCharaInf(const uint32_t & ModuleBase)
{
	auto funcaddress = (ModuleBase + 0x645B80);

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
