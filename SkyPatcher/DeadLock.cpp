#include "DeadLock.h"
#include <iostream>

using namespace std::string_literals;

DeadLock::DeadLock()
	:
	condition("Client.exe", "8D 4D 08 E8 ?? ?? ?? ?? 3D FC 53 00 00"s)
{
}
void DeadLock::Patch()
{
	if (!Patch_ChangeCondition())
		std::cout << "Patch Failed: DeadLock_ChangeCondition" << std::endl;

}
void DeadLock::UndoPatches()
{
	condition.UndoPatch();
}
bool DeadLock::Patch_ChangeCondition()
{
	if (!condition.GetAddress())
		return false;

	addr_return = condition.GetAddress().value() + 13;

	condition.WriteJump((uint32_t)Mod_DeadLock, 13);

	return true;
}
