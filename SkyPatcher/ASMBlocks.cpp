#include "ASMBlocks.h"

void __declspec(naked)  Rz::GrabArg()
{

	__asm
	{
		push ecx
		push eax
		
		//this loads an address 8-16 bytes before the first element
		lea ecx, Rz_

		//get the third argument for the box function from here
		mov eax, [ebp - 0x34]

		mov [ecx], eax
		pop eax
		pop ecx

		call edx
		sub eax, 0x00

		lea edx, Rz_

		mov edx, [edx + 0x08]

		jmp edx

	}
}



