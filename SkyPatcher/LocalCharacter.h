#pragma once
#include <stdint.h>
#include <string>
#include "MemoryClass.h"
#include <iostream>


//NOTE: need inline if defining in .h file. Header guards do not protect you from link-time multiple definitions

//allows us to define a function in another file and gives C linkage because c++ magles with function names
//and adds more complexity to code https://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c
extern  "C"
{
	void LCharaGrabBase();
}

class LocalChara
{
private:

	//structure layed out specifically so we can access the variables by the required offsets in assembly
	uint32_t addr_base = 0;
	uint32_t addr_return = 0;
	uint32_t addr_func = 0;
	std::string pttrn_charabase;
	static constexpr uint32_t off_health = 0x134;

public:

	LocalChara();
	void Patch(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);

private:
	bool Patch_GetBase(const std::vector<std::pair<uint32_t, uint32_t>> & ModuleAddresses);

};