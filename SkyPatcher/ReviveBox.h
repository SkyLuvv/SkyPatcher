#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>

extern "C"
{
	void ReviveBox_Pos();
	void ReviveBox_DimAndTransl();
}

class ReviveBox
{
private:
	//keep in mind everything is organized specifically because we access the members by offsets in our assembly code
	//having them static constexpr lays them out differently in memory. its easier to access them if they're just const
	//0h
	const uint32_t height = 0x190;
	//04h
	const uint32_t width = 0x258;
	//08h
	const uint32_t transluscency = 0x11;
	//0Ch
	uint32_t addr_rtn_position = 0;
	//10h
	uint32_t addr_rtn_dimandtransl = 0;
	//14h
	const uint32_t ypos = 0x90;

private:
	uint32_t addr_rtn_funcstatictext = 0;
	uint32_t addr_rtn_funcKUtext = 0;
	uint32_t arg_first = 0;
	int32_t arg_second = 1;
	uint32_t *arg_third = nullptr;
	void * pThis = *(void**)0x0344EB08;
	static constexpr uint32_t off_firstarg = 0x2748e78;
	static constexpr uint32_t addr_funccreatewindow = 0x011BE4D0;

private:

	std::string pttrn_KUtext;
	std::string pttrn_statictxtwindow;
	std::string pttrn_bypasstest;
	std::string pttrn_rtnmenuoption;
	std::string pttrn_position;
	std::string pttrn_dimandtransl;
	

	std::string pttrn_patch_rtnmenuoptn;

private:

	typedef void(__thiscall * Func)(void* pThis, uint32_t * first, int32_t flag, uint32_t * third);
	Func CreateRezBox = (Func)addr_funccreatewindow;

private:

	bool Patch_ByPassTest(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_ReturnRezMenuOption(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_KUtext(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_statictxtwindow(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_position(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	bool Patch_DimAndTransl(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);

public:
	ReviveBox();
	void Patch(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);
	void CreateReviveBox();
};

