#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::TimePassed()
{
	const duration<float> frameTime = steady_clock::now() - last;
	return frameTime.count();
}

void FrameTimer::Reset()
{
	last = steady_clock::now();
}
