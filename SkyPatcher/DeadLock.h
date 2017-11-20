#pragma once
#include "MemoryClass.h"
#include <stdint.h>
#include <string>
#include "Pattern.h"
#include "Mod.h"

extern "C"
{
	void Mod_DeadLock();
}

class DeadLock : public Mod
{
public:
	uint32_t datastart;
private:
	uint32_t addr_return = 0;
	Pattern condition;
	
public:
	DeadLock();
	virtual void Patch( )override;
	virtual void UndoPatches()override;

private:
//patch to change the condition of whether enemies are alive or not
	bool Patch_ChangeCondition();

};