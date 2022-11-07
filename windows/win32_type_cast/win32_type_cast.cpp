// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
// https://learn.microsoft.com/zh-tw/cpp/text/how-to-convert-between-various-string-types?view=msvc-170#converting-between-narrow-and-wide-strings
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winuser.h>
#include <atlbase.h>
#include <atlstr.h>
#include <atlconv.h>
#include <Shlwapi.h>
#include <string>
#include <string.h>
#include <sstream>

#define IDM_MENU1 9001
#define IDM_MENU2 9002
#define IDM_MENU3 9003
#define IDM_MENU4 9004
#define IDM_MENU5 9005
#define IDM_MENU6 9006
#define IDM_MENU7 9007
#define IDM_MENU8 9008
#define IDM_MENU9 9009
#define IDM_MENU10 9010
#define IDM_MENU11 9011
#define IDM_MENU12 9012
#define IDM_MENU13 9013
#define IDM_MENU14 9014
#define IDM_MENU15 9015
#define IDM_MENU16 9016
#define IDM_MENU17 9017
#define IDM_MENU18 9018
#define IDM_MENU19 9019
#define IDM_MENU20 9020
#define IDM_MENU21 9021
#define IDM_MENU22 9022

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HMENU hMenu = NULL;
HMENU hCast = NULL;
HMENU hCompare = NULL;
HMENU hAssignment = NULL;
HMENU hConnect = NULL;

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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
							LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			hMenu = CreateMenu();
			hCast = CreateMenu();
			hCompare = CreateMenu();
			hAssignment = CreateMenu();

			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hCast, TEXT("Cast"));
			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hCompare, TEXT("Compare"));
			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hAssignment,
					   TEXT("Assignment"));
			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hAssignment, TEXT("Connect"));

			// cast
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU1,
					   TEXT("ATL::CW2A wchar* to char*"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU2,
					   TEXT("ATL::CW2A char* to wchar*"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU3,
					   TEXT("int to wchar*"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU4,
					   TEXT("wchar* to int"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU5,
					   TEXT("sprintf int to char*"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU6,
					   TEXT("sscanf char* to int"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU7,
					   TEXT("stringstream int to char*"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU8,
					   TEXT("stringstream char* to int"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU7,
					   TEXT("stringstream int to char*"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU9,
					   TEXT("strtol char* to int"));
			AppendMenu(hCast, MF_STRING, (UINT_PTR)IDM_MENU10,
					   TEXT("stoi string to int"));
			// compare
			AppendMenu(hCompare, MF_STRING, (UINT_PTR)IDM_MENU11,
					   TEXT("strcmp string eq string"));
			AppendMenu(hCompare, MF_STRING, (UINT_PTR)IDM_MENU12,
					   TEXT("string.compare string eq string"));
			AppendMenu(hCompare, MF_STRING, (UINT_PTR)IDM_MENU13,
					   TEXT("strstr string eq string"));
			AppendMenu(hCompare, MF_STRING, (UINT_PTR)IDM_MENU14,
					   TEXT("string== string eq string"));
			// assignment
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU15,
					   TEXT("strncpy char* = char*"));
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU16,
					   TEXT("string.assign string = string"));
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU17,
					   TEXT("string = string"));
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU18,
					   TEXT("strcpy_s char* = char*"));
			// connect
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU19,
					   TEXT("strcat char*"));
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU21,
					   TEXT("string + string"));
			AppendMenu(hAssignment, MF_STRING, (UINT_PTR)IDM_MENU22,
					   TEXT("string append string"));
			SetMenu(hWnd, hMenu);
		}
		case WM_COMMAND:
			switch (wParam) {
				case IDM_MENU1: {
					wchar_t szText[] = L"hello world\0";
					char* text = ATL::CW2A(szText);
					MessageBoxA(hWnd, text, "alert", MB_OK);
				} break;
				case IDM_MENU2: {
					char szText[] = "hello world\0";
					wchar_t* text = ATL::CA2W(szText);
					MessageBoxW(hWnd, text, L"alert", MB_OK);
				} break;
				case IDM_MENU3: {
					wchar_t to[20];
					_itow_s(24, to, 10);
					MessageBoxW(hWnd, to, L"alert", MB_OK);
				} break;
				case IDM_MENU4: {
					wchar_t text[] = L"1024\0";
					int num = StrToInt(text);
					_itow_s(num, text, 10);
					MessageBoxW(hWnd, text, L"alert", MB_OK);
				} break;
				case IDM_MENU5: {
					char text[5];
					sprintf_s(text, "%d", 1024);
					MessageBoxA(hWnd, text, "alert", MB_OK);
				} break;
				case IDM_MENU6: {
					char text[] = "1024\0";
					int i;
					sscanf_s(text, "%d", &i);
					MessageBoxA(hWnd, std::to_string(i).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU7: {
					std::stringstream ss;
					ss << 1024;
					MessageBoxA(hWnd, ss.str().c_str(), "alert", MB_OK);
				} break;
				case IDM_MENU8: {
					std::stringstream ss;
					ss << "1024";
					int i;
					ss >> i;
					MessageBoxA(hWnd, std::to_string(i).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU9: {
					char text[] = "1024\0";
					char* end;
					int i = std::strtol(text, &end, 10);
					MessageBoxA(hWnd, std::to_string(i).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU10: {
					std::string text = "1024\0";
					int i = std::stoi(text);
					MessageBoxA(hWnd, std::to_string(i).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU11: {
					char textA[] = "1024\0";
					char textB[] = "1024\0";
					int reuslt = std::strcmp(textA, textB); // 0 eq
					MessageBoxA(hWnd, std::to_string(reuslt).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU12: {
					std::string textA = "1024\0";
					std::string textB = "1024\0";
					int reuslt = textA.compare(textB); // 0 eq
					MessageBoxA(hWnd, std::to_string(reuslt).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU13: {
					char textA[] = "1024\0";
					char textB[] = "1024\0";
					char* reuslt = std::strstr(textA, textB);
					MessageBoxA(hWnd, std::to_string(reuslt == NULL).c_str(),
								"alert", MB_OK);
				} break;
				case IDM_MENU14: {
					std::string textA = "1024\0";
					std::string textB = "1024\0";
					int reuslt = textA == textB;
					MessageBoxA(hWnd, std::to_string(reuslt).c_str(), "alert",
								MB_OK);
				} break;
				case IDM_MENU15: {
					char textA[] = "hello world\0";
					char textB[ARRAYSIZE(textA)] = "\0";
					strncpy_s(textB, textA, ARRAYSIZE(textA));
					MessageBoxA(hWnd, textB, "alert", MB_OK);
				} break;
				case IDM_MENU16: {
					std::string textA = "hello world\0";
					std::string textB = "\0";
					textB.assign(textA);
					MessageBoxA(hWnd, textB.c_str(), "alert", MB_OK);
				} break;
				case IDM_MENU17: {
					std::string textA = "hello world\0";
					std::string textB = "\0";
					textB = textA;
					MessageBoxA(hWnd, textB.c_str(), "alert", MB_OK);
				} break;
				case IDM_MENU18: {
					char textA[] = "hello world\0";
					char textB[ARRAYSIZE(textA)] = "\0";
					strcpy_s(textB, textA);
					MessageBoxA(hWnd, textB, "alert", MB_OK);
				} break;
				case IDM_MENU19: {
					char textA[] = "hello\0";
					char textB[ARRAYSIZE(textA)] = "world\0";
					strcat_s(textB, textA);
					MessageBoxA(hWnd, textB, "alert", MB_OK);
				} break;
				case IDM_MENU20: {
					std::string textA = "hello world\0";
					std::string textB = "\0";
					std::string textC = textA + textB;
					MessageBoxA(hWnd, textC.c_str(), "alert", MB_OK);
				} break;
				case IDM_MENU21: {
					std::string textA = "hello world\0";
					std::string textB = "\0";
					std::string textC = textA.append(textB);
					MessageBoxA(hWnd, textC.c_str(), "alert", MB_OK);
				} break;
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