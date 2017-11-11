#include "AutoInput.h"


using namespace std::chrono;
using namespace std::this_thread;

AutoInput::AutoInput(const uint32_t key, bool directinput)
	:
	directinput(directinput)

{
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	keyboard.type = INPUT_KEYBOARD;
	mouse.type = INPUT_MOUSE;


	if (this->directinput)
		keyboard.ki.wScan = key;
	else
		keyboard.ki.wVk = key;


}

void AutoInput::Hit(const uint32_t delay)
{
	keyboard.ki.dwFlags = 0;
	SendInput(1, &keyboard, sizeof(INPUT));

	sleep_for(milliseconds(delay));

	keyboard.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &keyboard, sizeof(INPUT));

}

void AutoInput::Click(const uint32_t delay)
{
	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, &mouse, sizeof(INPUT));

	sleep_for(milliseconds(delay));

	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &mouse, sizeof(INPUT));

}

void AutoInput::Click(const uint32_t X, const uint32_t Y, const uint32_t delay)
{

	mouse.mi.dx = (X * (0xFFFF / ScreenWidth));
	mouse.mi.dy = (Y * (0xFFFF / ScreenHeight));
	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN);

	SendInput(1, &mouse, sizeof(INPUT));

	sleep_for(milliseconds(delay));

	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &mouse, sizeof(INPUT));

}

void AutoInput::DownClick()
{
	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, &mouse, sizeof(INPUT));

}

void AutoInput::DownClick(const uint32_t X, const uint32_t Y)
{
	mouse.mi.dx = (X * (0xFFFF / ScreenWidth));
	mouse.mi.dy = (Y * (0xFFFF / ScreenHeight));
	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN);


}

void AutoInput::ReleaseClick()
{
	mouse.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &mouse, sizeof(INPUT));
}

void AutoInput::SwitchKey(const uint32_t key)
{
	if (directinput)
		keyboard.ki.wScan = key;
	else
		keyboard.ki.wVk = key;
}

void AutoInput::HitDown()
{
	keyboard.ki.dwFlags = 0;
	SendInput(1, &keyboard, sizeof(INPUT));
}

void AutoInput::HitUp()
{
	keyboard.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &keyboard, sizeof(INPUT));
}

uint32_t AutoInput::GetKey() const
{
	if (directinput)
		return keyboard.ki.wScan;
	else
		return keyboard.ki.wVk;
}