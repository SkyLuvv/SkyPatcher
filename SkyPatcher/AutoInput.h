#pragma once
#include "Windows.h"
#include "DirectInputDefines.h"
#include <stdint.h>
#include <chrono>
#include <thread>

class AutoInput
{
public:
	AutoInput();
	void Click(const uint32_t delay);

private:
	INPUT keyboard;
	INPUT mouse;
};