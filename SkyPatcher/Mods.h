#pragma once
#include "MemoryClass.h"
#include <stdint.h>
#include <string>

extern "C"
{
	void Mod_DeadLock();
}

class DeadLock
{
private:
	uint32_t addr_return = 0;
	std::string pttrn_condition;
	
public:
	DeadLock();
	void Patch(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses);

private:
//patch to change the condition of whether enemies are alive or not
	bool Patch_ChangeCondition(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses);

};