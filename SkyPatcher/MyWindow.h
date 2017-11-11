#pragma once
#include "WindowsIncludes.h"
#include <stdint.h>
#include <string>

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
	virtual LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void ShowMessageBox(const std::string & Message, const std::string & Title)const;

private:
	HWND hWnd;
	HINSTANCE hInst = nullptr;
	static constexpr char * Title = "SkyLuv Hack Menu";
	static constexpr char * WndClassName = "SkyLuv Hack Menu";

public:
	static constexpr unsigned int Height = 500;
	static constexpr unsigned int Width = 500;
};

class Button
{
public:
	Button() = default;
	Button(HWND m_hWnd, size_t X, size_t Y, size_t width, size_t height, const std::string & type, const std::string & text, const uint32_t ID = 0)
	{
		this->ID = ID;
		hWnd = CreateWindowEx(NULL, type.c_str(), text.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE, X, Y, width, height, m_hWnd, (HMENU)this->ID, NULL, NULL);
	}
	void Create(HWND m_hWnd, size_t X, size_t Y, size_t width, size_t height, const std::string & type, const std::string & text, const uint32_t ID = 0)
	{
		this->ID = ID;
		hWnd = CreateWindowEx(NULL, type.c_str(), text.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE, X, Y, width, height, m_hWnd, (HMENU)this->ID, NULL, NULL);
	}
	void SetText(const std::string & text)
	{
		SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)text.c_str());
	}
	void SetFont(HFONT hfont)
	{
		SendMessage(hWnd, WM_SETFONT, (WPARAM)hfont, (LPARAM)MAKELONG(TRUE, 0));
	}
	uint32_t GetID()const
	{
		return ID;
	}
	HWND GethWnd()const
	{
		return hWnd;
	}

private:
	HWND hWnd;
	uint32_t ID;
};