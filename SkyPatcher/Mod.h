#pragma once

class Mod
{
public:
	virtual void Patch() = 0;
	virtual void UndoPatches() = 0;
	
	enum class ID
	{
		DeadLock,
		ReviveBox,
		LocalChara,
		First = DeadLock,
		Last = LocalChara
	};

};