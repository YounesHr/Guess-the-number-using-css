#include <Windows.h>
#include <iostream>
#include <string>
#include <string.h>

// Global Variables
HINSTANCE hInstance;         //the current instance
const char* WindowTitle;     //The title of the window
const char* WindowClassName; //the class name

LRESULT    CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM); //Used for getting messages and stuff from e.g, moving your mouse
WNDCLASS               RegisterWindowClass(HINSTANCE); //registers the class in windows so you can show it
BOOL                   InitInstance(HINSTANCE, int);  //initialises the class and window

void                   InitVariables(); //used to declare the window title, class name, etc.

#define DefaultWindowStyle (WS_POPUP | WS_HSCROLL | WS_SYSMENU | WS_CAPTION| WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX |WS_TABSTOP| WS_MAXIMIZEBOX)

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE prevInstance /*this is always null*/, PSTR cmdLineArgs, INT cmdShow)
{
	InitVariables();

	//the & fetches the address of the RegisterWindowClass "variable" so it can be pointed to. cpp magic basically

	if (!InitInstance(hInstance, cmdShow))
		return FALSE;

	MSG msg{};
	//this will be running forever until the window is closed. GetMessage constantly loops getting system messages like mouse moves, etc
	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}

//Setting up the variable init thing
void InitVariables()
{
	WindowTitle     = "A title here";
	WindowClassName = "A class name here";
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: //clicking the X button on the window basically
		PostQuitMessage(0); //tells the program to exit
		break;
	default:
		return DefWindowProcA(hWnd, msg, wParam, lParam);
		break;
	}
}

WNDCLASS RegisterWindowClass(HINSTANCE instance)
{
	WNDCLASS wc{};
	wc.hInstance = instance;
	wc.lpszClassName = WindowClassName;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WndProc;
	return wc;
}

BOOL InitInstance(HINSTANCE instance, int cmdShow)
{
	hInstance = instance; //stores the global instance as this method's instance

	HWND hWnd =
		CreateWindowA(
			WindowClassName, WindowTitle,     //Gives it the class and title
			DefaultWindowStyle,               //Window style
			CW_USEDEFAULT, CW_USEDEFAULT,     //initial window position
			900 /*width*/, 450/*height*/,
			nullptr, nullptr, hInstance, nullptr
		);

	if (!hWnd)
		return FALSE; //same as 0

	ShowWindow(hWnd, cmdShow); //actually shows the window on your screen
	UpdateWindow(hWnd);
	return TRUE; //lets other code know it's shown correctly
}