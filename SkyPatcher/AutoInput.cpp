#include "AutoInput.h"

AutoInput::AutoInput()
{
	mouse.type = INPUT_MOUSE;
}

void AutoInput::Click(const uint32_t delay)
{
	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, &mouse, sizeof(INPUT));

	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &mouse, sizeof(INPUT));

}
