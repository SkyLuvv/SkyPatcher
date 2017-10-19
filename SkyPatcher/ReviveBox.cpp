#pragma once
#include "ReviveBox.h"

 ReviveBox::ReviveBox()
{
	using namespace std::string_literals;


	pttrn_KUtext = "\x6A\x00\x8B\x4D\xBC\x6A"s;

	pttrn_statictxtwindow = "\x6A\x00\x6A\x00\x6A\x00\x6A\x04\x68\xFF"s;

	pttrn_bypasstest = "\xE8\x05\x1C\x1B\xFF\x85\xC0\x0F\x84\x57\x4A\x00\x00"s;

	pttrn_rtnmenuoption = "\x50\xE8\x0C\x99\x48\xFF"s;
	
	pttrn_position = "\xD1\xFB\x83\xC7\x50"s;

	pttrn_dimandtransl = "\xE4\x6A\x04\x6A\x28\x68\xC8\x00\x00\x00"s;

	pttrn_patch_rtnmenuoptn = "\xB8\x13\x00\x00\x00"s;
	
	//initialize the first argument.
	auto ClientBase = Memory::GetModuleAddress("Client.exe");
	arg_first = ClientBase + off_firstarg;
}

 void ReviveBox::Patch(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 using namespace std;
	 
	if (!(Patch_ByPassTest(ModuleAddresses)))
		cout << "Patch Failed : Patch_ByPassTest" << endl;

	if (!(Patch_ReturnRezMenuOption(ModuleAddresses)))
		cout << "Patch Failed : Patch_ReturnRezMenuOption" << endl;

	if (!(Patch_statictxtwindow(ModuleAddresses)))
		cout << "Patch Failed : Patch_statictxtwindow" << endl;

	if (!(Patch_KUtext(ModuleAddresses)))
		cout << "Patch Failed : Patch_KUtext" << endl;

	if (!Patch_position(ModuleAddresses))
		cout << "Patch Failed : Patch_position" << endl;

	if (!Patch_DimAndTransl(ModuleAddresses))
	    cout << "Patch Failed : Patch_DimandTransl" << endl;
	
}

 void ReviveBox::CreateReviveBox()
{
	 if(arg_first)
	  CreateRezBox(pThis, (uint32_t*)arg_first, arg_second, arg_third);
}

 bool ReviveBox::Patch_ByPassTest(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_bypasstest);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 13);

	return true;
}

 bool ReviveBox::Patch_ReturnRezMenuOption(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_rtnmenuoption);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 6);
	
	 Memory::WriteToMemory((char*)addr, pttrn_patch_rtnmenuoptn);
	
	return true;
}

 bool ReviveBox::Patch_KUtext(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_KUtext);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 45);

	return true;
}

 bool ReviveBox::Patch_statictxtwindow(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
{
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_statictxtwindow);

	 if (!addr)
		 return false;

	 Memory::WriteNop((char*)addr, 50);

	return true;
}

 bool ReviveBox::Patch_position(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
 {
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_position);

	 if (!addr)
		 return false;

	 addr_rtn_position = addr + 5;

	 Memory::WriteNop((char*)addr, 5);

	 Memory::WriteJump((char*)addr, (uint32_t)ReviveBox_Pos);

	 return true;
 }

 bool ReviveBox::Patch_DimAndTransl(const std::vector<std::pair<uint32_t, uint32_t>>& ModuleAddresses)
 {
	 auto addr = Memory::FindPattern(ModuleAddresses, pttrn_dimandtransl);

	 if (!addr)
		 return false;

	 //increase once since its a memory address before where we need to patch
	 ++addr;

	 addr_rtn_dimandtransl = addr + 9;

	 Memory::WriteNop((char*)addr, 9);

	 Memory::WriteJump((char*)addr, (uint32_t)ReviveBox_DimAndTransl);

	 return true;
 }

