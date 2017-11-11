#pragma once

#include "Windows.h"
#include <stdint.h>
#include <chrono>
#include <thread>

class AutoInput
{
public:
	AutoInput() = delete;
	AutoInput(const uint32_t key, bool directinput);
	void Hit(const uint32_t delay);
	void Click(const uint32_t delay);
	void Click(const uint32_t X, const uint32_t Y, const uint32_t delay);
	void DownClick();
	void DownClick(const uint32_t X, const uint32_t Y);
	void ReleaseClick();
	void SwitchKey(const uint32_t key);
	void HitDown();
	void HitUp();
	uint32_t GetKey()const;
private:
	INPUT keyboard;
	INPUT mouse;
	uint32_t ScreenWidth;
	uint32_t ScreenHeight;
	bool directinput;
};