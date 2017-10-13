#pragma once
#include <vector>
#include <map>
#include <stdint.h>
#include "Windows.h"


class Memory
{
public:
	static uint32_t FindPattern(const std::vector<std::pair<uint32_t, uint32_t>>&pages, const std::string & pattern);
	static std::vector<std::pair<uint32_t, uint32_t>> GetAllModuleAddresses();
	static void WriteJump(char *SourceAddress, uint32_t  DestAddress, uint32_t nopsize = 5);
	static uint32_t GetModuleAddress(const std::string & Module);
	static void Memory::WriteToMemory(char *membase, const std::string & bytes);
	static void Memory::WriteNop(char *membase, const size_t & size);
};