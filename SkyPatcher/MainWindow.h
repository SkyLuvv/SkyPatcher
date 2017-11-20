#pragma once
#include "WindowsIncludes.h"
#include <stdint.h>
#include <string>
#include "Mouse.h"
#include "DimensionStructs.h"

class MainWindow
{

public:
	MainWindow(HINSTANCE hInst);
	~MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	void Kill()
	{
		PostQuitMessage(0);
	}
	bool IsActive()const;
	bool IsMinimized()const;
	bool ProcessMessage();
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void ShowMessageBox(const std::string & Message, const std::string & Title);
	const HWND GetHWND()const
	{
		return hWnd;
	}

private:
	HWND hWnd;
	HINSTANCE hInst = nullptr;
	static constexpr char * Title = "SKY'S DX11 HACK MENU";
	static constexpr char * WndClassName = "SKY'S DX11 HACK MENU";
	static constexpr char * Icon = "Sky\\SkyIcon.ico";
public:
	static constexpr int Height = 230;
	static constexpr int Width = 450;
	Mouse mouse;
};