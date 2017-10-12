#pragma once
#include <vector>
#include <map>
#include <stdint.h>
#include "Windows.h"

class Memory
{
public:
	static int FindPattern(const std::vector<std::pair<int32_t, int32_t>>&pages, const std::string & pattern);
	static std::vector<std::pair<int32_t, int32_t>> GetAllModuleAddresses();
	static void WriteJump(char *SourceAddress, int32_t  DestAddress, int32_t nopsize = 5);
};