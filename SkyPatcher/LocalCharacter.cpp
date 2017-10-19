#include "LocalCharacter.h"

LocalChara::LocalChara()
{
	//lets us ignores the null terminator for c-strings in the middle of our string so it gets the length from start to end
	//example usage : "\x80\x00\x30"s
	using namespace std::string_literals;

	pttrn_charabase = "\x66\x8B\x81\xC4\x01\x00\x00"s;

}

void LocalChara::Patch(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	if (!(Patch_GetBase(ModuleAddresses)))
		std::cout << "Patched Failed : Patch_GetBase" << std::endl;
}

float LocalChara::GetHealth()const
{
	if (!addr_base)
		return 1.0f;

	return *(float*)(addr_base + off_health);
}

void LocalChara::SetHealth(float newHealth)
{
	if (!addr_base)
		return;

	*(float*)(addr_base + off_health) = newHealth;
}

bool LocalChara::Patch_GetBase(const std::vector<std::pair<uint32_t, uint32_t>>  & ModuleAddresses)
{
	addr_func = Memory::FindPattern(ModuleAddresses, pttrn_charabase);

	if (!addr_func)
		return false;

	addr_return = addr_func + 0x07;

	Memory::WriteJump((char*)addr_func, (uint32_t)LChara_GrabBase, 7);

	return true;
}
