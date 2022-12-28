// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
// https://blogs.windows.com/windowsdeveloper/2015/06/05/using-ffmpeg-in-windows-applications/
// https://github.com/Microsoft/FFmpegInterop
// https://stackoverflow.com/questions/2401764/can-ffmpeg-be-used-as-a-library-instead-of-a-standalone-program
// https://trac.ffmpeg.org/wiki/Projects
// https://blog.csdn.net/weixin_45032957/article/details/116447520?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-116447520-blog-79367721.pc_relevant_3mothn_strategy_and_data_recovery&spm=1001.2101.3001.4242.1&utm_relevant_index=3
// https://github.com/BtbN/FFmpeg-Builds/releases
#ifndef UNICODE
#define UNICODE
#include <process.h>
#endif

#include <iostream>
#include <string.h>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <vector>
#include <stdint.h>
#include <atlbase.h>
#include <atlconv.h>

#pragma comment(linker, "/subsystem:windows") /// SUBSYSTEM:CONSOLE

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ComDlg32.Lib")

#define IDM_MENU_SUB 4001
#define IDM_MENU_START 4002
#define IDM_MENU_STOP 4003

HWND hWnd;
HMENU hMenu = NULL;
HMENU mSubMenu = NULL;
HANDLE myHandle;
HANDLE ghMutex;

DWORD WINAPI getFrameThread(__in LPVOID lpParameter) {
	unsigned int& myCounter = *((unsigned int*)lpParameter);
	while (myCounter < 0xFFFFFFFF) {
		++myCounter;
	}
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
							LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			hMenu = CreateMenu();
			mSubMenu = CreateMenu();

			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_START,
					   TEXT("Start Thread"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_STOP,
					   TEXT("Stop Thread"));

			SetMenu(hWnd, hMenu);
		}
		case WM_COMMAND:
			switch (wParam) {
				case IDM_MENU_START: {
					unsigned int myCounter = 0;
					DWORD myThreadID;
					myHandle = CreateThread(0, 0, getFrameThread, &myCounter, 0,
											&myThreadID);

				} break;
				case IDM_MENU_STOP:
					CloseHandle(myHandle);
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PWSTR pCmdLine, int nCmdShow) {
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
