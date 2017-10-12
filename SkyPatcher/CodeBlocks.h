#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>

//NOTE: need inline if defining in .h file. Header guards do not protect you from link-time multiple definitions

//lets us ignores the null terminator for c-strings in the middle of our string so it gets the length from start to end
//example usage : "\x80\x00\x30"s
using namespace std::string_literals;

class LocalChara
{
public:
	uint32_t off_health = 0x134;
	uint32_t addr_base = 0;
	uint32_t addr_func = 0;
	uint32_t addr_return = 0;
	std::string pttrn_charabase = "\x66\x8B\x81\xC4\x01\x00\x00"s;
public:
	static void GrabBase();
	void Patch(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
private:
	bool Patch_GetBase(const std::vector<std::pair<int32_t,int32_t>> & ModuleAddresses);

}; static LocalChara LChara;



class ReviveBox
{
public:
    uint32_t arg_first = 0;
    uint32_t arg_second = 5;
    uint32_t *arg_third = nullptr;
	void * pThis = *(void**)0x0344EB08;

	uint32_t off_firstarg = 0x2748e78;

    uint32_t addr_rtn_funcgrabargs = 0;
	uint32_t addr_rtn_funcstatictext = 0;
	uint32_t addr_rtn_funcKUtext = 0;

    uint32_t addr_funccreatewindow = 0x011BE4D0;
	uint32_t addr_funcgrabargs = 0;
	uint32_t addr_funcstatictext = 0;


public:
	std::string pttrn_funcgrabargs =  "\xFF\xD2\x83\xE8\x00\x0F\x84\x58\x01\x00\x00\x48\x0F"s ;
	std::string pttrn_funcKUtext = "\x6A\x00\x8B\x4D\xBC\x6A"s;
	std::string pttrn_funcstatictxtwindow = "\x6A\x00\x6A\x00\x6A\x00\x6A\x04\x68\xFF"s;

public:
    typedef void(__thiscall * Func)(void* pThis, void* first, int32_t flag, void* third);
	Func CreateRezBox = (Func)addr_funccreatewindow;
public:
    static void GrabArg();
	void Patch(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
private:

	bool Patch_GetArg(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
	bool Patch_ByPassTest(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
	bool Patch_ReturnRezMenuOption(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
	bool Patch_KUtext(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);
	bool Patch_statictxtwindow(const std::vector<std::pair<int32_t, int32_t>> & ModuleAddresses);

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

inline void LocalChara::Patch(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	if (!(Patch_GetBase(ModuleAddresses)))
		std::cout << "Patched Failed : Patch_GetBase" << std::endl;
	
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

		mov [edx]RevBox.arg_third , eax

		pop edx

		call edx
		sub eax, 0x00

		lea edx, RevBox
		
		jmp [edx]RevBox.addr_rtn_funcgrabargs
	}
}

inline void ReviveBox::Patch(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	if (!(Patch_GetArg(ModuleAddresses)))
		std::cout << "Patch Failed : Patch_GetArg" << std::endl;


}

inline bool ReviveBox::Patch_GetArg(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	addr_funcgrabargs = Memory::FindPattern(ModuleAddresses, pttrn_funcgrabargs);

	if (!addr_funcgrabargs)
		return false;
	
	addr_rtn_funcgrabargs = addr_funcgrabargs + 0x05;

	auto ClientBase = Memory::GetModuleAddress("Client.exe");

	if (!ClientBase)
		return false;
	
	arg_first = ClientBase + off_firstarg;

	Memory::WriteJump((char*)addr_funcgrabargs, (int32_t)GrabArg);

	return true;
}

inline bool ReviveBox::Patch_ByPassTest(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	return false;
}

inline bool ReviveBox::Patch_ReturnRezMenuOption(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	return false;
}

inline bool ReviveBox::Patch_KUtext(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	return false;
}

inline bool ReviveBox::Patch_statictxtwindow(const std::vector<std::pair<int32_t, int32_t>>& ModuleAddresses)
{
	return false;
}

