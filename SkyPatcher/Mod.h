#pragma once

enum class modID
{
	DeadLock = 1,
	ReviveBox,
	LocalChara
};

class Mod
{
public:
	Mod(uint32_t ID, std::string & Name)
		:
		ID(ID),
		Name(std::move(Name))
	{}
	virtual void Patch() = 0;
	virtual void UndoPatches() = 0;
	bool IsPatched() { return patched; }
	uint32_t GetID() { return ID; }
	std::string GetName() { return Name; }
protected:
	uint32_t ID;
	bool patched;
	std::string Name;
};

