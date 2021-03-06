#include "MainWindow.h"



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

	auto myicon = (HICON)LoadImage(NULL, Icon, IMAGE_ICON, 0, 0,
		LR_LOADFROMFILE |  // we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |   // default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED);    //Title bar Icon

	if (!myicon)
	{
		ShowMessageBox("ERROR", "Couldn't Load Icon...");
		exit(1);
	}


	M_Window::ptr = this;

	WNDCLASSEX wc = { 0 };    //Create a new extended windows class

	wc.cbSize = sizeof(WNDCLASSEX);    //Size of our windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;    //class styles
	wc.lpfnWndProc = WndProc;    //Default windows procedure function
	wc.hInstance = hInst;    //Instance to current application
	wc.hIcon = myicon;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);    //Default mouse Icon
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);    //Window bg color
	wc.lpszClassName = WndClassName;    //Name of our windows class
	wc.hIconSm = NULL; //Icon in your taskbar

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
		WS_BORDER | WS_SYSMENU  | WS_MINIMIZEBOX,
		200,                   // x-position of the window
		200,                   // y-position of the window
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

void MainWindow::ShowMessageBox(const std::string & Message, const std::string & Title)
{
	MessageBox(0, Message.c_str(), Title.c_str(), MB_OK);
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
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnMouseMove((float)pt.x, (float)pt.y);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed((float)pt.x, (float)pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
	
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed((float)pt.x, (float)pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased((float)pt.x, (float)pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased((float)pt.x, (float)pt.y);
		break;
	}

	// ************ END MOUSE MESSAGES ************ //
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}