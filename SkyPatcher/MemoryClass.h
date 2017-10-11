#pragma once
#include <vector>
#include <map>
#include <stdint.h>

class Memory
{
public:
	static int FindPattern(const std::vector<std::pair<int, int>>&pages, const std::string & pattern);
	static std::vector<std::pair<int, int>> GetAllModuleAddresses();
	static void WriteJump(char *SourceAddress, uint32_t   DestAddress);
};