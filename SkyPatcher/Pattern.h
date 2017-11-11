#pragma once
#include "MemoryClass.h"
#include <algorithm>


class Pattern
{
public:
	Pattern() = delete;
	Pattern(const std::string & Pattern);
	Pattern(const std::string & Module, const std::string & Pattern);
	Pattern(const Pattern &) = default;
	void WriteBytes(const std::string & NewBytes);
	void WriteByte(const std::string & byte, size_t length);
	void WriteJump(uintptr_t Dest, size_t nopsize = 5);
	void UndoPatch();
	std::optional<uintptr_t> GetAddress()const;
	void SetAddress(uintptr_t NewAddress);
	void ClearStoredBytes();
private:
	void Format(std::string & p);
	std::optional<std::string> GetFormatted(std::string  p);
	void StoreBytes(size_t length);

private:
	uintptr_t baseaddress = 0;
	std::string originalbytes;
	std::string pattern;
};