#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>
#include "Pattern.h"
#include "Mod.h"

//NOTE: need inline if defining in .h file. Header guards do not protect you from link-time multiple definitions

//allows us to define a function in another file and gives C linkage because c++ magles with function names
//and adds more complexity to code https://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c
extern  "C"
{
	void LChara_GrabBase();
}

class LocalChara : public Mod
{
private:

	//structure layed out specifically so we can access the variables by the required offsets in assembly
	uint32_t addr_base = 0;
	uint32_t addr_return = 0;
	uint32_t addr_func = 0;
	Pattern charabase;
	static constexpr uint32_t off_health = 0x1A8;

public:

	LocalChara();
	uintptr_t GetBase()const;
	virtual void Patch() override;
	virtual void UndoPatches() override;
	float GetHealth()const;
	void SetHealth(float newHealth);

private:
	bool Patch_GetBase();

};