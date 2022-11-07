// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
#ifndef UNICODE
#define UNICODE
#endif

#include <stdint.h>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <atlstr.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ComDlg32.Lib")
#pragma comment(lib, "gdi32.lib")

#define IDM_MENU1 9001
#define IDM_MENU2 9002
#define IDM_MENU3 9003
#define IDM_MENU4 9004
#define IDM_MENU5 9005
#define IDM_MENU6 9006

#define WIDTH 256
#define HEIGHT 256

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HMENU hMenu = NULL;
HMENU hSubMenu = NULL;
HINSTANCE hInst = NULL;

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

wchar_t* PickImageFile() {
	wchar_t* szPath = new wchar_t[MAX_PATH];
	OPENFILENAME ofn = {sizeof(ofn)}; // common dialog box structure
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = L"*.bmp\0";
	ofn.lpstrFile = szPath;
	ofn.nMaxFile = sizeof(wchar_t) * MAX_PATH;

	BOOL fOk = GetOpenFileName(&ofn);
	if (fOk) {
		return szPath;
	}
	return nullptr;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
							LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			hMenu = CreateMenu();
			hSubMenu = CreateMenu();

			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Menu"));
			AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU1,
					   TEXT("Pick File"));
			AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU2,
					   TEXT("Window To unsigned int"));
			AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU3,
					   TEXT("uint8_t to HBITMAP"));
			AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU4,
					   TEXT("Make Text MemDC"));
			AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU5,
					   TEXT("MemDC to BYTE*"));

			SetMenu(hWnd, hMenu);
		}
		case WM_COMMAND:
			switch (wParam) {
				case IDM_MENU1: {
					wchar_t* szPath = PickImageFile();
					if (NULL == szPath)
						break;
					HDC hdc = GetDC(hWnd);
					HDC hmemdc = CreateCompatibleDC(hdc);
					HBITMAP hBitmap = (HBITMAP)LoadImage(
						hInst, szPath, IMAGE_BITMAP, LR_DEFAULTSIZE,
						LR_DEFAULTSIZE, LR_LOADFROMFILE);
					SelectObject(hmemdc, hBitmap);
					BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hmemdc, 0, 0, SRCCOPY);
					DeleteObject(hBitmap);
					ReleaseDC(hWnd, hmemdc);
					delete[] szPath;
				} break;
				case IDM_MENU2: {
					wchar_t* szPath = PickImageFile();
					if (NULL == szPath)
						break;

					FILE* f;
					fopen_s(&f, ATL::CW2A(szPath), "rb");
					unsigned int* buffer = new unsigned int[256 * 256];
					fseek(f, 54, 0);
					fread(buffer, 256 * 256 * 4, 1, f);
					fclose(f);
					delete[] szPath;
					MessageBox(hWnd, std::to_wstring(buffer[0]).c_str(),
							   L"alert", MB_OK);
				} break;
				case IDM_MENU3: {
					uint32_t arr[240 * 120];
					std::fill(arr, arr + sizeof(arr) / sizeof(*arr),
							  RGB(255, 0, 0));
					// or std::fill(arr, arr + 240 * 120, RGB(255, 0, 0));
					HBITMAP hBitmap = CreateBitmap(240, 120, 1, 32, (void*)arr);
					MessageBox(hWnd, L"clicked menu3", L"alert", MB_OK);
				} break;
				case IDM_MENU4: {
					// https://learn.microsoft.com/zh-cn/windows/win32/gdi/capturing-an-image
					HDC hdcScreen = GetDC(NULL);
					HDC hdcWindow = GetDC(hWnd);
					HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
					HBITMAP hBitmap =
						CreateCompatibleBitmap(hdcWindow, 256, 256);
					SelectObject(hdcMemDC, hBitmap);
					RECT rc = {0, 0, 120, 30};

					wchar_t text[] = L"hello";
					DrawText(hdcMemDC, text, ARRAYSIZE(text) - 1, &rc,
							 DT_SINGLELINE | DT_NOCLIP);
					BitBlt(hdcWindow, 0, 0, WIDTH, HEIGHT, hdcMemDC, 0, 0,
						   SRCCOPY);

					DeleteObject(hdcMemDC);
					ReleaseDC(hWnd, hdcWindow);
					ReleaseDC(NULL, hdcScreen);
				} break;
				case IDM_MENU5: {

					HDC hdcWindow = GetDC(hWnd);
					HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
					HDC hdcMemDC2 = CreateCompatibleDC(hdcWindow);
					HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, 10, 10);
					SelectObject(hdcMemDC, hBitmap);

					RECT rc = {0, 0, 10, 10};
					HBRUSH brush = CreateSolidBrush(0x0000FF);
					FillRect(hdcMemDC, &rc, brush);

					BYTE* lpPixels = new BYTE[10 * 10 * 4];
					GetBitmapBits(hBitmap, 10 * 10 * 4, lpPixels);

					std::string json = "";
					for (size_t y = 0; y < 10; y++) {
						for (size_t x = 0; x < 10; x++) {
							size_t index = x + y * 10;
							json +=
								std::to_string((int)(lpPixels[index])) + ",";
						}
					}

					MessageBoxA(hWnd, json.c_str(), "alert", MB_OK);

					BitBlt(hdcWindow, 0, 0, WIDTH, HEIGHT, hdcMemDC, 0, 0,
						   SRCCOPY);

					DeleteObject(hdcMemDC);
					ReleaseDC(hWnd, hdcWindow);
					delete[] lpPixels;
				} break;
				case IDM_MENU6: {
					const int width = 256;
					const int height = 256;
					uint8_t data[width * height * 4];
					HINSTANCE hInst = GetModuleHandle(NULL);
					HWND hWnd = GetActiveWindow();
					wchar_t szPath[MAX_PATH] = {};
					OPENFILENAME ofn = {
						sizeof(ofn)}; // common dialog box structure
					ofn.hwndOwner = hWnd;
					ofn.lpstrFilter = L"*.bmp\0";
					ofn.lpstrFile = szPath;
					ofn.nMaxFile = ARRAYSIZE(szPath);

					BOOL fOk = GetOpenFileName(&ofn);
					if (!fOk)
						break;

					HBITMAP hBitmap = (HBITMAP)LoadImage(
						hInst, szPath, IMAGE_BITMAP, width, height,
						LR_LOADFROMFILE); // load image

					BYTE* lpPixels =
						new BYTE[width * height * 4]; // b,g,r,reserved
					GetBitmapBits(hBitmap, width * height * 4, lpPixels);

					for (size_t y = 0; y < height; y++) {
						for (size_t x = 0; x < width; x++) {
							size_t index = x + y * width;
							data[index * 4 + 0] = lpPixels[index * 4 + 2];
							data[index * 4 + 1] = lpPixels[index * 4 + 1];
							data[index * 4 + 2] = lpPixels[index * 4 + 0];
							data[index * 4 + 3] = 255;
						}
					}

					DeleteObject(hBitmap);
					delete[] lpPixels;
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