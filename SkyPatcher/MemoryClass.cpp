#include "MemoryClass.h"
#include <iostream>

std::optional<uintptr_t> Memory::ScanAllPages(const std::vector<std::pair<uintptr_t, size_t>>& pages, const std::string & pattern)
{
	
	for (auto currPage = pages.begin(); currPage != pages.end(); std::advance(currPage,1))
	{

		//.first is the start address of our page
		auto currAddress = (size_t)currPage->first;

		//the end of the page is the start address + the size of the page (.second) minues the length of our pattern
		//since we don't want to scan  invalid memory
		auto EndofPage = (size_t)(currPage->first + currPage->second) - pattern.length();

		for (; currAddress < EndofPage; ++currAddress)
		{
			bool found = true;

			for (size_t x = 0; x < pattern.length(); ++x)
			{
				if (pattern[x] == '?')
				{
				}
				else if ((uint8_t)pattern[x] != *(uint8_t*)(currAddress + x))
				{
					found = false; break;
				}

			}
			if (found)
				return currAddress;
		}
	}
	return {};
}

std::optional<uintptr_t> Memory::ScanModule(const std::pair<uintptr_t, size_t>& page, const std::string & pattern)
{

	auto currAddress = (size_t)page.first;
	auto EndofPage = (size_t)(page.first + page.second) - pattern.length();

	for (; currAddress < EndofPage; ++currAddress)
	{
		bool found = true;


		if (IsBadReadPtr((void*)currAddress, pattern.length()) != 0)
			continue;

		for (size_t x = 0; x < pattern.length(); ++x)
		{
			if (pattern[x] == '?')
			{
			}
			else if ((uint8_t)pattern[x] != *(uint8_t*)(currAddress + x))
			{
				found = false; break;
			}

		}
		if (found)
			return currAddress;
	}

	return {};
}

std::optional<std::vector<std::pair<uintptr_t, size_t>>> Memory::GetPageAddressesAndSize()
{
	using namespace std;

	//this struct will hold the information of the memory pages we are going to scan
	MEMORY_BASIC_INFORMATION MemoryBasicInf;

	//start with our module so that we don't begin with scanning heap/stack memory and such
	auto address = (uintptr_t)GetModuleHandle(0);

	int32_t dwProtect = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

	vector<pair<uintptr_t, size_t> > pages;

	for (; VirtualQuery((uintptr_t*)address, &MemoryBasicInf, sizeof(MemoryBasicInf));
		address = (uintptr_t)(MemoryBasicInf.BaseAddress) + MemoryBasicInf.RegionSize)
	{
		if ((MemoryBasicInf.State & MEM_COMMIT)
			&& !(MemoryBasicInf.Protect & dwProtect)
			&& (MemoryBasicInf.Type & MEM_IMAGE))
		{
			//store the base address and the size of the page
			pages.emplace_back(address, MemoryBasicInf.RegionSize);
		}
	}


	if (pages.empty())
		return {};

	return pages;

}

std::optional<MODULEINFO> Memory::GetModuleInfo(const std::string & ModuleName)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = (HMODULE)GetModuleAddress(ModuleName).value_or(0);

	if (!hModule) 
		return {};

	if (GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO)))
		return modinfo;
	else
		return {};

}

std::optional<std::pair<uintptr_t, size_t>> Memory::GetModuleAddressAndSize(const std::string & ModuleName)
{
	auto ModuleInfo = GetModuleInfo(ModuleName);

	if (ModuleInfo)
		return std::make_pair((uintptr_t)ModuleInfo.value().lpBaseOfDll, (size_t)ModuleInfo.value().SizeOfImage);
	else
		return {};

}

void Memory::WriteJump(uint8_t *SourceAddress, uintptr_t  DestAddress, size_t nopsize)
{
	DWORD oldProtection;
	uintptr_t relativeAddress;

	
	//give that address read and write permissions and store the old permissions at oldProtection
	//pass in 5 because a jump only modifies 5 bytes
	VirtualProtect(SourceAddress, nopsize, PAGE_EXECUTE_READWRITE, &oldProtection);

	//Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
	//The offset is relative to the end of the JMP instruction and not the beginning so we have to subtract 5 from it
	//in order to get the exact memory address of the function we are jumping to, otherwise, since it's relative to the END 
	//of the jmp instruction, we'll be telling it to jmp 5 bytes 

	//another in-depth explanation, so jmp says "how far away from THIS JUMP we are trying to go" , so it doesn't count itself
	//it goes to the next instruction in memory and thats where it starts counting off from, because thats how far away from itself
	//we are trying to go, so that would make us jump 5 bytes too far, so we need to subtract 5.
	//for example : EB f8f8f8f8  jmp f8f8f8f8
	//              fd ab 08     mov eax,ebx
	// that is saying jump f8f8f8f8 bytes away from itself
	//so it doesnt count the beginning of itself it counts away from itself, which is starting the next byte fd 

	//relativeAddress is how far away from the SourceAddress we need to jump, to get to the destinationAddress
	relativeAddress = (uintptr_t)(DestAddress - (uintptr_t)SourceAddress) - 5;

	//nop the bytes first before writing our jump
	for (size_t i = 0; i < nopsize; ++i)
		*(SourceAddress + i) = 0x90;

	// Write the JMP opcode at our jump position...
	//takes up one byte
	*SourceAddress = 0xE9;

	// Write the offset to where we're gonna jump
	//The instruction will then become JMP ff002123 for example
	//dereference it as a 4 byte ptr, because the addresses take up 4 bytes
	*((uint32_t*)(SourceAddress + 0x01)) = relativeAddress;

	// Restore the default permissions
	VirtualProtect(SourceAddress, nopsize, oldProtection, nullptr);
}

std::optional<uintptr_t> Memory::GetModuleAddress(const std::string & Module)
{
	auto address = (uintptr_t)(GetModuleHandle(Module.c_str()));

	if (address)
		return address;

	return {};
}

void Memory::WriteBytes(uint8_t *membase, const std::string & bytes)
{
	DWORD oldProtection;

	VirtualProtect(membase, bytes.length(), PAGE_EXECUTE_READWRITE, &oldProtection);

	for (size_t i = 0; i < bytes.length(); ++i)
	{
		*(membase + i) = bytes[i];
	}

	VirtualProtect(membase, bytes.length(), oldProtection, nullptr);
}

void Memory::WriteByte(uint8_t * membase, const size_t & size, const unsigned char byte)
{
	DWORD oldProtection;
	//give that address read and write permissions and store the old permissions at oldProtection
	VirtualProtect(membase, size , PAGE_EXECUTE_READWRITE, &oldProtection);

	for (size_t i = 0; i < size ; ++i)
	{
		*(membase + i) = byte;
	}

	// Restore the default permissions
	VirtualProtect(membase, size, oldProtection, nullptr);
}


