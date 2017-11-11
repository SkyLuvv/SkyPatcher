#include "MyWindow.h"

namespace M_Window
{
	MainWindow * ptr = nullptr;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (M_Window::ptr)
		return M_Window::ptr->HandleMessage(hWnd, msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);

}


MainWindow::MainWindow(HINSTANCE hInst)
	:
	hInst(hInst)
{

	M_Window::ptr = this;

	WNDCLASSEX wc;    //Create a new extended windows class

	wc.cbSize = sizeof(WNDCLASSEX);    //Size of our windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;    //class styles
	wc.lpfnWndProc = WndProc;    //Default windows procedure function
	wc.cbClsExtra = NULL;    //Extra bytes after our wc structure
	wc.cbWndExtra = NULL;    //Extra bytes after our windows instance
	wc.hInstance = hInst;    //Instance to current application
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);    //Title bar Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);    //Default mouse Icon
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);    //Window bg color
	wc.lpszMenuName = NULL;    //Name of the menu attached to our window
	wc.lpszClassName = WndClassName;    //Name of our windows class
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); //Icon in your taskbar

	if (!RegisterClassEx(&wc))
	{
		//if registration failed, display error
		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	// set the size, but not the position
	RECT wr = { 0, 0, Width, Height };
	// adjust the size
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);


	hWnd = CreateWindowEx(0,
		wc.lpszClassName,
		Title,
		WS_OVERLAPPEDWINDOW,
		300,                   // x-position of the window
		300,                   // y-position of the window
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,    // height of the window
		nullptr,
		nullptr,
		this->hInst,
		nullptr);

	if (!hWnd)
	{
		ShowMessageBox("Error Creating Window.", "Error");
		exit(1);
	}

	//Shows our window
	ShowWindow(hWnd, SW_SHOW);
	//Its good to update our window
	UpdateWindow(hWnd);

}

MainWindow::~MainWindow()
{
	//unregister window class
	UnregisterClass(WndClassName, hInst);
}

bool MainWindow::IsActive()const
{
	return GetActiveWindow() == hWnd;
}

bool MainWindow::IsMinimized()const
{
	return IsIconic(hWnd) != 0;
}

bool MainWindow::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

void MainWindow::ShowMessageBox(const std::string & Message, const std::string & Title)const
{
	MessageBox(hWnd, Message.c_str(), Title.c_str(), MB_OK);
}

LRESULT MainWindow::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		// ************ KEYBOARD MESSAGES ************ //
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:

		break;
	case WM_CHAR:

		break;
		// ************ END KEYBOARD MESSAGES ************ //

		// ************ MOUSE MESSAGES ************ //
	case WM_MOUSEMOVE:
	{

	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		break;
	}
	case WM_RBUTTONDOWN:
	{

		break;
	}
	case WM_LBUTTONUP:
	{
		break;
	}
	case WM_RBUTTONUP:
	{

		break;
	}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		// ************ END MOUSE MESSAGES ************ //
	}

}