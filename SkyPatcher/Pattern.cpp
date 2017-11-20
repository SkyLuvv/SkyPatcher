#include "Pattern.h"
#include <string>


Pattern::Pattern(const std::string & Pattern)
	:
	pattern(Pattern)
{
	if (!pattern.empty())
	{
		Format(pattern);
		auto ModuleAddresses = Memory::GetPageAddressesAndSize();

		if (ModuleAddresses)
		{
			auto address = Memory::ScanAllPages(ModuleAddresses.value(), pattern);

			if (address)
				baseaddress = address.value();
		}
	}
}

Pattern::Pattern(const std::string & Module, const std::string & Pattern)
	:
	pattern(Pattern)
{
	if (!pattern.empty())
	{
		Format(pattern);
		auto ModuleAddress = Memory::GetModuleAddressAndSize(Module);

		if (ModuleAddress)
		{

			auto address = Memory::ScanModule(ModuleAddress.value(), pattern);

			if (address)
				baseaddress = address.value();
		}
	}
}

void Pattern::WriteBytes(const std::string & NewBytes)
{
	if (!baseaddress)
		return;

	if (originalbytes.empty())
	 StoreBytes(NewBytes.length());

	auto formatted = GetFormatted(NewBytes);
	if(formatted)
	  Memory::WriteBytes((uint8_t*)baseaddress, formatted.value());
}

void Pattern::WriteByte(const std::string & byte, size_t length)
{
	if (!baseaddress)
		return;

	if (originalbytes.empty())
	 StoreBytes(length);

	auto formatted = GetFormatted(byte);
	if(formatted)
	 Memory::WriteByte((uint8_t*)baseaddress, length, formatted.value()[0] );
}

void Pattern::WriteJump(uintptr_t Dest, size_t nopsize)
{
	if (!baseaddress)
		return;

	if (originalbytes.empty())
	 StoreBytes(nopsize);

	Memory::WriteJump((uint8_t*)baseaddress, Dest, nopsize);
}

void Pattern::UndoPatch()
{
	if (originalbytes.empty())
	    return;

	Memory::WriteBytes((uint8_t*)baseaddress, originalbytes);
}

void Pattern::SetAddress(uintptr_t NewAddress)
{
	baseaddress = NewAddress;
}

void Pattern::ClearStoredBytes()
{
	originalbytes.clear();
}

std::optional<uintptr_t> Pattern::GetAddress()const
{
	if (baseaddress)
		return baseaddress;
	return {};
}

void Pattern::Format(std::string & p)
{
	// Remove spaces from the pattern string.
	p.erase(remove_if(p.begin(), p.end(), isspace), p.end());

	std::string temp;
	for (auto it = p.begin(); it != p.end(); std::advance(it, 2))
	{
		try
		{
			auto byte = p.substr(it - p.begin(), 2);

			if (byte.compare("??") == 0)
				temp.push_back('?');
			else if (byte.compare("**") == 0)
				temp.push_back('?');
			else
				//convert the byte to a hex interpretation
				temp.push_back(std::stoi(byte.c_str(), nullptr, 16));
		}
		catch (...)
		{
			return;
		}
	}

	p = std::move(temp);
	p.shrink_to_fit();
}

std::optional<std::string> Pattern::GetFormatted(std::string p)
{
	// Remove spaces from the pattern string.
	p.erase(remove_if(p.begin(), p.end(), isspace), p.end());

	std::string temp;
	for (auto it = p.begin(); it != p.end(); std::advance(it, 2))
	{
		try
		{
			auto byte = p.substr(it - p.begin(), 2);

			if (byte.compare("??") == 0)
				temp.push_back('?');
			else if (byte.compare("**") == 0)
				temp.push_back('?');	
			else
				//convert the byte to a hex interpretation
				temp.push_back(std::stoi(byte.c_str(), nullptr, 16));
		}
		catch (...)
		{
			return{};
		}
	}

	return temp;
}

void Pattern::StoreBytes(size_t length)
{
	if (!baseaddress)
		return;

	for (size_t i = 0; i < length; ++i)
	{
		originalbytes.push_back(*(uint8_t*)(baseaddress + i));
	}
}
