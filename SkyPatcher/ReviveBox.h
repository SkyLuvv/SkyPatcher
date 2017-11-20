#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>
#include "Pattern.h"
#include "Mod.h"

extern "C"
{
	void ReviveBox_Pos();
	void ReviveBox_DimAndTransl();
}

class ReviveBox : public Mod
{
public:
	uint32_t datastart;
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
	void * pThis = *(void**)0x0355DEF8;
	static constexpr uint32_t off_firstarg = 0x28186C8;
	static constexpr uint32_t addr_funccreatewindow = 0x012488D0;

	
	std::string pttrn_patch_rtnmenuoptn;
	Pattern kutext;
	Pattern bypasstest;
	Pattern statictxt;
	Pattern dimandtransl;
	Pattern position;
	Pattern rtnoption;

private:

	typedef void(__thiscall * Func)(void* pThis, uint32_t * first, int32_t flag, uint32_t * third);
	Func CreateRezBox = (Func)addr_funccreatewindow;

private:
	bool Patch_ByPassTest();
	bool Patch_ReturnRezMenuOption();
	bool Patch_KUtext();
	bool Patch_statictxtwindow();
	bool Patch_position();
	bool Patch_DimAndTransl();

public:
	ReviveBox();
	virtual void Patch() override;
    virtual void UndoPatches() override;
	void CreateReviveBox();
};

