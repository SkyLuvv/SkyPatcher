#pragma once
#include <vector>
#include <map>
#include <stdint.h>
#include "WindowsIncludes.h"
#include <optional>
#include <Psapi.h>

namespace Memory
{
	std::optional<uintptr_t> ScanAllPages(const std::vector<std::pair<uintptr_t, size_t>>&pages, const std::string & pattern);
	std::optional<uintptr_t> ScanModule(const std::pair<uintptr_t, size_t>&page, const std::string & pattern);
	std::optional<std::vector<std::pair<uintptr_t, size_t>>> GetPageAddressesAndSize();
	std::optional<MODULEINFO> GetModuleInfo(const std::string & ModuleName);
	std::optional<std::pair<uintptr_t, size_t>> GetModuleAddressAndSize(const std::string & ModuleName);
	void WriteJump(uint8_t *SourceAddress, uintptr_t  DestAddress, size_t nopsize = 5);
	std::optional<uintptr_t> GetModuleAddress(const std::string & Module);
	void WriteBytes(uint8_t *membase, const std::string & bytes);
	void WriteByte(uint8_t * membase, const size_t & size, const unsigned char byte);

};