#include <Windows.h>
#include <iostream>
#include <string>
#include <string.h>


HINSTANCE hInstance;         
const char* WindowTitle;     
const char* WindowClassName; 

LRESULT    CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
WNDCLASS               RegisterWindowClass(HINSTANCE);
BOOL                   InitInstance(HINSTANCE, int);

void                   InitVariables();

#define DefaultWindowStyle (WS_POPUP | WS_HSCROLL | WS_SYSMENU | WS_CAPTION| WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX |WS_TABSTOP| WS_MAXIMIZEBOX)

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE prevInstance , PSTR cmdLineArgs, INT cmdShow)
{
	InitVariables();

	

	if (!InitInstance(hInstance, cmdShow))
		return FALSE;

	MSG msg{};
	
	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}


void InitVariables()
{
	WindowTitle     = "A title here";
	WindowClassName = "A class name here";
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
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
	hInstance = instance;

	HWND hWnd =
		CreateWindowA(
			WindowClassName, WindowTitle,   
			DefaultWindowStyle,               
			CW_USEDEFAULT, CW_USEDEFAULT,     
			900 , 450,
			nullptr, nullptr, hInstance, nullptr
		);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
