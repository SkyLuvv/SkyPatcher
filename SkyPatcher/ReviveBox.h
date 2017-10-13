#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>

extern "C"
{
	void GrabThirdArg();
}
class ReviveBox
{

public:
	ReviveBox();
	void Patch(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	void CreateReviveBox();

private:
	uint32_t arg_first = 0;
	int32_t arg_second = 5;
	uint32_t *arg_third = nullptr;

	uint32_t addr_rtn_funcgrabargs = 0;
	uint32_t addr_rtn_funcstatictext = 0;
	uint32_t addr_rtn_funcKUtext = 0;

	void * pThis = *(void**)0x0344EB08;

	static constexpr uint32_t off_firstarg = 0x2748e78;
	static constexpr uint32_t addr_funccreatewindow = 0x011BE4D0;

private:
	std::string pttrn_funcgrabargs;
	std::string pttrn_funcKUtext;
	std::string pttrn_funcstatictxtwindow;
	std::string pttrn_funcbypasstest;
	std::string pttrn_funcrtnmenuoption;

	std::string pttrn_patch_funcrtnmenuoptn;

private:

	typedef void(__thiscall * Func)(void* pThis, uint32_t * first, int32_t flag, uint32_t * third);
	Func CreateRezBox = (Func)addr_funccreatewindow;

private:

	bool Patch_GetArg(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_ByPassTest(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_ReturnRezMenuOption(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_KUtext(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_statictxtwindow(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);

};

