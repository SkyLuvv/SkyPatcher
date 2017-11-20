#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include "DeadLock.h"
#include "ReviveBox.h"
#include "LocalCharacter.h"
#include "Enumeration.h"
#include "Mod.h"


class Sky
{
public:
	Sky();
	void Main(HMODULE hModule);
	void CreateConsole();
	void CreateReviveThread();

public:
	bool AutoReviveOn = true;
	static constexpr float speed_RevBox = 0.0f;
	static constexpr uint32_t speed_EBOT = 50;

public:
	std::unordered_map<modID, Mod*> modsmap;
	std::unique_ptr<ReviveBox> RevBox;
	std::unique_ptr<LocalChara> LChara;
	std::unique_ptr<DeadLock> DL;
};

void AutoRevive(Sky * sky);
