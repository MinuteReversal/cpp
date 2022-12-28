// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
#ifndef UNICODE
#define UNICODE
#include <sstream>
#include <tchar.h>
#endif

#include <ostream>
#include <windows.h>
#include <winuser.h>
#include <queue>

#define IDM_MENU1 9001
#define IDM_MENU2 9002
#define IDM_MENU3 9003

#pragma comment(lib, "user32.lib")

HWND hWnd;
HINSTANCE hInst;
HMENU hMenu = NULL;
HMENU mSubMenu = NULL;
std::queue<int> q;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PWSTR pCmdLine, int nCmdShow) {
	hInst = hInstance; // Store instance handle in our global variable
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	hWnd = CreateWindowEx(0,          // Optional window styles.
						  CLASS_NAME, // Window class
						  L"Learn Win32 To Program Windows", // Window text
						  WS_OVERLAPPEDWINDOW,               // Window style

						  // Size and position
						  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
						  CW_USEDEFAULT,

						  NULL,      // Parent window
						  NULL,      // Menu
						  hInstance, // Instance handle
						  NULL       // Additional application data
	);

	if (hWnd == NULL) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);

	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
							LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			hMenu = CreateMenu();
			mSubMenu = CreateMenu();

			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU1, TEXT("Menu1"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU2, TEXT("Menu2"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU3, TEXT("Menu3"));

			SetMenu(hWnd, hMenu);
		}
		case WM_COMMAND:
			switch (wParam) {
				case IDM_MENU1: {
					q.push(q.size() + 1);
					std::wostringstream woss;
					woss << q.size();
					MessageBox(hWnd, woss.str().c_str(), L"alert", MB_OK);
				} break;
				case IDM_MENU2: {
					q.pop();
					std::wostringstream woss;
					woss << q.size();
					MessageBox(hWnd, woss.str().c_str(), L"alert", MB_OK);
				} break;
				case IDM_MENU3:
					MessageBox(hWnd, L"menu3 clicked", L"alert", MB_OK);
					break;
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hWnd, &ps);
		}
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}