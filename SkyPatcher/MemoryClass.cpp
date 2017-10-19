#include "MemoryClass.h"
#include <iostream>

uint32_t Memory::FindPattern(const std::vector<std::pair<uint32_t, uint32_t>>& pages, const std::string & pattern)
{
	for (size_t currPage = 0; currPage < pages.size(); ++currPage)
	{
		//.first is the start address of our page
		auto currAddress = pages[currPage].first;

		//the end of the page is the start address + the size of the page (.second) minues the length of our pattern
		//since we don't want to scan  invalid memory
		auto EndofPage = (uint32_t)(pages[currPage].first + pages[currPage].second) - pattern.length();

		for (; currAddress < EndofPage; ++currAddress)
		{
			bool found = true;

			for (size_t x = 0; x < pattern.length(); ++x)
			{
				if (pattern[x] == '?')
				{
				}
				else if (pattern[x] != *(char*)(currAddress + x))
				{
					found = false; break;
				}

			}
			if (found)
				return currAddress;
		}
	}
	return 0;
}

std::vector<std::pair<uint32_t, uint32_t>> Memory::GetAllModuleAddresses()
{
	using namespace std;

	//this struct will hold the information of the memory pages we are going to scan
	MEMORY_BASIC_INFORMATION MemoryBasicInf;

	//start with our module so that we don't begin with scanning heap/stack memory and such
	auto address = (uint32_t)GetModuleHandle(0);

	int32_t dwProtect = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

	vector<pair<uint32_t, uint32_t> > pages;

	for (; VirtualQuery((uint32_t*)address, &MemoryBasicInf, sizeof(MemoryBasicInf));
		address = (uint32_t)(MemoryBasicInf.BaseAddress) + MemoryBasicInf.RegionSize)
	{
		if ((MemoryBasicInf.State & MEM_COMMIT)
			&& !(MemoryBasicInf.Protect & dwProtect)
			&& (MemoryBasicInf.Type & MEM_IMAGE))
		{
			//store the base address and the size of the page
			pages.push_back(make_pair(address, MemoryBasicInf.RegionSize));
		}
	}
	return pages;
}

void Memory::WriteJump(char *SourceAddress, uint32_t  DestAddress, uint32_t nopsize)
{
	DWORD oldProtection;
	int32_t relativeAddress;

	
	//give that address read and write permissions and store the old permissions at oldProtection
	//pass in 5 because a jump only modifies 5 bytes
	VirtualProtect(SourceAddress, 5, PAGE_EXECUTE_READWRITE, &oldProtection);

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
	relativeAddress = (uint32_t)(DestAddress - (uint32_t)SourceAddress) - 5;

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
	VirtualProtect(SourceAddress, 5, oldProtection, nullptr);
}

uint32_t Memory::GetModuleAddress(const std::string & Module)
{
	return (uint32_t)(GetModuleHandle(Module.c_str()));
}

void Memory::WriteToMemory(char *membase, const std::string & bytes)
{
	DWORD oldProtection;

	VirtualProtect(membase, bytes.length(), PAGE_EXECUTE_READWRITE, &oldProtection);

	for (size_t i = 0; i < bytes.length(); ++i)
	{
		*(membase + i) = bytes[i];
	}

	VirtualProtect(membase, bytes.length(), oldProtection, nullptr);
}

void Memory::WriteNop(char * membase, const size_t & size)
{
	DWORD oldProtection;
	//give that address read and write permissions and store the old permissions at oldProtection
	VirtualProtect(membase, size , PAGE_EXECUTE_READWRITE, &oldProtection);

	for (size_t i = 0; i < size ; ++i)
	{
		*(membase + i) = 0x90;
	}

	// Restore the default permissions
	VirtualProtect(membase, size, oldProtection, nullptr);
}
