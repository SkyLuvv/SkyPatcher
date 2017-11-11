#pragma once
#include "MyWindow.h"
#include <vector>
#include "Enumeration.h"
#include "Mod.h"

class Interface : public MainWindow
{
public:
	Interface(HMODULE hModule) : MainWindow(hModule) {};
	virtual LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
	void CreateButton(HWND m_hWnd, size_t X, size_t Y, size_t width, size_t height, const std::string & type, const std::string & text, const uint32_t ID = 0);
	std::vector<Button> GetButtons()const
	{
		return buttons;
	}

private:
	std::vector<Button> buttons;

};