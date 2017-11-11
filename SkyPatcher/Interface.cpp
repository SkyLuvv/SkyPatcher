#include "Interface.h"

LRESULT Interface::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
	{
		for (auto ID : Enum<Mod::ID>())
		{
			if ((WPARAM)ID == wParam)
			{

			}
		}
	}

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);

	}
}

void Interface::CreateButton(HWND m_hWnd, size_t X, size_t Y, size_t width, size_t height, const std::string & type, const std::string & text, const uint32_t ID)
{
	buttons.emplace_back(m_hWnd, X, Y, width, height, type, text, ID);
}
