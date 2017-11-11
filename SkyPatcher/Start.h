#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include "DeadLock.h"
#include "ReviveBox.h"
#include "LocalCharacter.h"
#include "Enumeration.h"

namespace Sky
{
	void main(HMODULE hModule);
	void Init();
	void CreateMyConsole();
	bool CreateConnection();
	void ReviveThread();
	void BotThread();
	void ApplyPatches();


	static constexpr float speed_RevBox = 0.3f;
	static constexpr uint32_t speed_EBOT = 50;



	static std::vector<std::unique_ptr<Mod>> Mods;
};