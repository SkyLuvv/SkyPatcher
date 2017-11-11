#pragma once
#include <vector>
#include <map>
#include <stdint.h>
#include "WindowsIncludes.h"
#include <optional>
#include <Psapi.h>

class Memory
{
public:
	static std::optional<uintptr_t> ScanAllPages(const std::vector<std::pair<uintptr_t, size_t>>&pages, const std::string & pattern);
	static std::optional<uintptr_t> ScanModule(const std::pair<uintptr_t, size_t>&page, const std::string & pattern);
	static std::optional<std::vector<std::pair<uintptr_t, size_t>>> GetPageAddressesAndSize();
	static std::optional<MODULEINFO> GetModuleInfo(const std::string & ModuleName);
	static std::optional<std::pair<uintptr_t, size_t>> GetModuleAddressAndSize(const std::string & ModuleName);
	static void WriteJump(uint8_t *SourceAddress, uintptr_t  DestAddress, size_t nopsize = 5);
	static std::optional<uintptr_t> GetModuleAddress(const std::string & Module);
	static void WriteBytes(uint8_t *membase, const std::string & bytes);
	static void WriteByte(uint8_t * membase, const size_t & size, const unsigned char byte);

};