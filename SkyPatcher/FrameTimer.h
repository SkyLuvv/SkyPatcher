#pragma once
#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float TimePassed();
	void Reset();
private:
	std::chrono::steady_clock::time_point last;
};