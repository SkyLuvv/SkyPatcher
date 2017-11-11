#include "LocalCharacter.h"

using namespace std::string_literals;

LocalChara::LocalChara()
	:
	charabase("Client.exe", "D9 86 D0 02 00 00 D9 45 FC DE D9"s)
{
	//lets us ignores the null terminator for c-strings in the middle of our string so it gets the length from start to end
	//example usage : "\x80\x00\x30"s

}

uintptr_t LocalChara::GetBase() const
{
	return addr_base;
}

void LocalChara::Patch()
{

	if (!(Patch_GetBase()))
		std::cout << "Patched Failed: LocalChara_GetBase" << std::endl;
}

void LocalChara::UndoPatches()
{
	charabase.UndoPatch();
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

bool LocalChara::Patch_GetBase()
{

	if (charabase.GetAddress())
		addr_return = charabase.GetAddress().value() + 6;
	else
		return false;

	charabase.WriteJump((uintptr_t)LChara_GrabBase, 6);

	return true;
}
