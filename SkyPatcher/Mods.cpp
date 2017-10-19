#include "Mods.h"
#include <iostream>

DeadLock::DeadLock()
{
	using namespace std::string_literals;

	pttrn_condition = "\x8D\x4D\x08\xE8\x34\x2E\x28\x01"s;
	
}

void DeadLock::Patch(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	if (!Patch_ChangeCondition(ModuleAddresses))
		std::cout << "Patch Failed : Patch_ChangeCondition" << std::endl;

}

bool DeadLock::Patch_ChangeCondition(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	auto addr = Memory::FindPattern(ModuleAddresses, pttrn_condition);

	if (!addr)
		return false;

	addr_return = addr + 13;

	Memory::WriteNop((char*)addr, 13);

	Memory::WriteJump((char*)addr, (uint32_t)Mod_DeadLock);

	return true;
}
