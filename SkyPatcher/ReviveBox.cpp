#pragma once
#include "ReviveBox.h"

 ReviveBox::ReviveBox()
{
	using namespace std::string_literals;

	pttrn_funcgrabargs = "\xFF\xD2\x83\xE8\x00\x0F\x84\x58\x01\x00\x00\x48\x0F"s;
	pttrn_funcKUtext = "\x6A\x00\x8B\x4D\xBC\x6A"s;
	pttrn_funcstatictxtwindow = "\x6A\x00\x6A\x00\x6A\x00\x6A\x04\x68\xFF"s;
	pttrn_funcbypasstest = "\xE8\x05\x1C\x1B\xFF\x85\xC0\x0F\x84\x57\x4A\x00\x00"s;
	pttrn_funcrtnmenuoption = "\x50\xE8\x0C\x99\x48\xFF"s;


	pttrn_patch_funcrtnmenuoptn = "\xB8\x13\x00\x00\x00"s;
}


 void ReviveBox::Patch(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 using namespace std;

	if (!(Patch_GetArg(ModuleAddresses)))
		cout << "Patch Failed : Patch_GetArg" << endl;

	if (!(Patch_ByPassTest(ModuleAddresses)))
		cout << "Patch Failed : Patch_ByPassTest" << endl;

	if (!(Patch_ReturnRezMenuOption(ModuleAddresses)))
		cout << "Patch Failed : Patch_ReturnRezMenuOption" << endl;

	if (!(Patch_statictxtwindow(ModuleAddresses)))
		cout << "Patch Failed : Patch_statictxtwindow" << endl;

	if (!(Patch_KUtext(ModuleAddresses)))
		cout << "Patch Failed : Patch_KUtext" << endl;


}

 void ReviveBox::CreateReviveBox()
{
	CreateRezBox(pThis, (uint32_t*)arg_first, arg_second, arg_third);
}

 bool ReviveBox::Patch_GetArg(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	auto addr = Memory::FindPattern(ModuleAddresses, pttrn_funcgrabargs);

	if (!addr)
		return false;

	addr_rtn_funcgrabargs = addr + 0x05;

	auto ClientBase = Memory::GetModuleAddress("Client.exe");

	if (!ClientBase)
		return false;

	arg_first = ClientBase + off_firstarg;

	Memory::WriteJump((char*)addr, (uint32_t)GrabThirdArg);

	return true;
}

 bool ReviveBox::Patch_ByPassTest(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_funcbypasstest);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 13);

	return true;
}

 bool ReviveBox::Patch_ReturnRezMenuOption(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_funcrtnmenuoption);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 6);
	
	 Memory::WriteToMemory((char*)addr, pttrn_patch_funcrtnmenuoptn);
	
	return true;
}

 bool ReviveBox::Patch_KUtext(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_funcKUtext);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 45);

	return true;
}

 bool ReviveBox::Patch_statictxtwindow(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_funcstatictxtwindow);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 50);

	return true;
}

