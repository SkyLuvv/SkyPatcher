#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>
//NOTE: need inline if defining in .h file. Header guards do not protect you from link-time multiple definitions


class LocalChara
{
public:
	uint32_t off_health = 0x134;
	uint32_t addr_base = 0;
	uint32_t addr_func = 0;
	uint32_t addr_return = 0;
	std::string pttrn_charabase = "\x66\x8B\x81\xC4\x01\x00\x00";
public:
	static void GrabBase();
	bool Patch(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
private:
	bool Patch_GetBase(const std::vector<std::pair<int32_t,int32_t>> & ModuleAddresses);

}; static LocalChara LChara;

class ReviveBox
{
public:
    uint32_t firstarg = 0;
    uint32_t secondarg = 5;
    uint32_t *thirdarg = nullptr;
    uint32_t    addr_return = 0;
    void * pThis = *(void**)0x0344EB08;
    uint32_t addr_func = 0;
	uint32_t addr_funcgrabargs = 0;
	uint32_t off_firstarg = 0x2748e78;


    typedef void(__thiscall * Func)(void* pThis, void* first, int32_t flag, void* third);
    Func Func_ = (Func)addr_func;
public:
    static void GrabArg();
	bool Patch(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
private:

	bool Patch_GetArg(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
	bool Patch_ByPassTest(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
	bool Patch_ReturnRezMenuOption(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);

}; static ReviveBox RevBox;

inline void __declspec(naked) LocalChara::GrabBase()
{
	__asm
	{

		lea edx, LChara

		mov[edx]LChara.addr_base, ecx

		mov ax, [ecx + 0x000001C4]

		jmp[edx]LChara.addr_return

	}
}

inline bool LocalChara::Patch(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	if (!(Patch_GetBase(ModuleAddresses)))
	{
		std::cout << "Patched Failed : Patch_GetBase" << std::endl;
		return false;
	}

	return true;
}

inline bool LocalChara::Patch_GetBase(const std::vector<std::pair<int32_t, int32_t>>  & ModuleAddresses)
{
	addr_func = Memory::FindPattern(ModuleAddresses, pttrn_charabase);

	if (!addr_func)
		return false;

	addr_return = addr_func + 0x07;

	Memory::WriteJump((char*)addr_func, (int32_t)GrabBase, 7);

	return true;
}


inline void __declspec(naked) ReviveBox::GrabArg()
{
	__asm
	{

		push edx
		lea edx , RevBox

		mov eax, dword ptr[ebp - 0x34]

		mov [edx]RevBox.thirdarg , eax

		pop edx

		call edx
		sub eax, 0x00

		push edx
		lea edx, RevBox
		
		jmp [edx]RevBox.addr_return

	}
}