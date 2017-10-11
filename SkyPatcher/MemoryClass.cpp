#include "MemoryClass.h"
#include "Windows.h"

int Memory::FindPattern(const std::vector<std::pair<int, int>>& pages, const std::string & pattern)
{
	for (unsigned int currPage = 0; currPage < pages.size(); ++currPage)
	{
		//.first is the start address of our page
		int currAddress = pages[currPage].first;

		//the end of the page is the start address + the size of the page (.second) minues the length of our pattern
		//since we don't want to scan  invalid memory
		int EndofPage = (pages[currPage].first + pages[currPage].second) - pattern.length();

		for (; currAddress < EndofPage; ++currAddress)
		{
			bool found = true;

			for (unsigned int x = 0; x < pattern.size(); ++x)
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

std::vector<std::pair<int, int>> Memory::GetAllModuleAddresses()
{
	using namespace std;

	//this struct will hold the information of the memory pages we are going to scan
	MEMORY_BASIC_INFORMATION MemoryBasicInf;


	//start with our module so that we don't begin with scanning heap/stack memory and such
	int address = (int)GetModuleHandle(0);

	//the protection flags we are going to look for in the page. if it's equal to one of these, don't 
	//push it into our vector
	int dwProtect = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

	vector<pair<int, int> > pages;


	//iterate through the pages in memory and store the base and size in our std::pair
	//if virtualquery returns 0 that means it can't scan the memory further, so break out
	for (; VirtualQuery((int*)address, &MemoryBasicInf, sizeof(MemoryBasicInf));
		//add the base addr of the page we are on with its size to get to the next
		//page in memory, and store in address, so we can query for information on each page
		address = (int)(MemoryBasicInf.BaseAddress) + MemoryBasicInf.RegionSize)


	{

		//Check if the memory is commited, not reserved/free.
		//check the access protections of the page (Protect) and whether it's an image (mbi.Type)
		//which means it should be a module
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

void Memory::WriteJump(char *SourceAddress, uint32_t  DestAddress)
{
	DWORD oldProtection;
	int relativeAddress;

	
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
	relativeAddress = (int)((int)DestAddress - (int)SourceAddress) - 5;

	// Write the JMP opcode at our jump position...
	//takes up one byte
	*SourceAddress = 0xE9;

	// Write the offset to where we're gonna jump
	//The instruction will then become JMP ff002123 for example
	//dereference it as a 4 byte ptr, because the addresses take up 4 bytes
	*((int*)(SourceAddress + 0x01)) = relativeAddress;

	// Restore the default permissions
	VirtualProtect(SourceAddress, 5, oldProtection, nullptr);
}