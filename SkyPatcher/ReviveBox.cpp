#pragma once
#include "ReviveBox.h"

using namespace std::string_literals;

 ReviveBox::ReviveBox()
	 :
 Mod((uint32_t)modID::ReviveBox, (std::string)"REVIVE MODS"),
 kutext("Client.exe", "6A 00 8B 4D BC 6A"s),
 bypasstest("Client.exe", "E8 95 72 12 FF"s),
 statictxt("Client.exe", "6A 00 6A 00 6A 00 6A 04 68 FF"s),
 rtnoption("Client.exe", "50 E8 0C 00 41 FF"s),
 dimandtransl("Client.exe", "E4 6A 04 6A 28 68 C8 00 00 00"s),
 position("Client.exe", "D1 FB 83 C7 50"s)
{
	pttrn_patch_rtnmenuoptn = "B8 13 00 00 00"s;
	
	//increase once since its a memory address before where we need to patch
	if(dimandtransl.GetAddress())
	  dimandtransl.SetAddress(dimandtransl.GetAddress().value() + 1);

	//initialize the first argument.
	auto ClientBase = Memory::GetModuleAddress("Client.exe").value_or(0);
	arg_first = ClientBase + off_firstarg;
}
 
 void ReviveBox::Patch()
{
	 using namespace std;
	 
	if (!(Patch_ReturnRezMenuOption()))
		cout << "Patch Failed : ReviveBox_ReturnRezMenuOption" << endl;
	
	if (!(Patch_statictxtwindow()))
		cout << "Patch Failed : ReviveBox_statictxtwindow" << endl;

	if (!(Patch_KUtext()))
		cout << "Patch Failed : ReviveBox_KUtext" << endl;

	if (!Patch_position())
		cout << "Patch Failed : ReviveBox_position" << endl;

	if (!Patch_DimAndTransl())
	    cout << "Patch Failed : ReviveBox_DimandTransl" << endl;
	
	if (!(Patch_ByPassTest()))
		cout << "Patch Failed : ReviveBox_ByPassTest" << endl;
		
	patched = true;
}

 void ReviveBox::UndoPatches()
 {
	 bypasstest.UndoPatch();
	 rtnoption.UndoPatch();
	 kutext.UndoPatch();
	 statictxt.UndoPatch();
	 position.UndoPatch();
	 dimandtransl.UndoPatch();

	 patched = false;
 }

 void ReviveBox::CreateReviveBox()
{
	 if(arg_first)
	  CreateRezBox(pThis, (uint32_t*)arg_first, arg_second, arg_third);
}

 bool ReviveBox::Patch_ByPassTest()
{
	 if (!bypasstest.GetAddress())
		 return false;

	 bypasstest.WriteByte("90", 13);

	return true;
}

 bool ReviveBox::Patch_ReturnRezMenuOption()
{
	 if (!rtnoption.GetAddress())
		 return false;

	 rtnoption.WriteByte("90", 6);
	 rtnoption.WriteBytes(pttrn_patch_rtnmenuoptn);

	return true;
}

 bool ReviveBox::Patch_KUtext()
{
	 if (!kutext.GetAddress())
		 return false;

	 kutext.WriteByte("90",45);

	return true;
}

 bool ReviveBox::Patch_statictxtwindow()
{
	 if (!statictxt.GetAddress())
		 return false;

	 statictxt.WriteByte("90", 50);

	return true;
}

 bool ReviveBox::Patch_position()
 {
	 if (!position.GetAddress())
		 return false;

    addr_rtn_position = position.GetAddress().value() + 5;

	position.WriteJump((uint32_t)ReviveBox_Pos);

	 return true;
 }

 bool ReviveBox::Patch_DimAndTransl()
 {

	 if (!dimandtransl.GetAddress())
		 return false;

	 addr_rtn_dimandtransl = dimandtransl.GetAddress().value() + 9;

	 dimandtransl.WriteByte("90", 9);

	 dimandtransl.WriteJump((uint32_t)ReviveBox_DimAndTransl);

	 return true;
 }

