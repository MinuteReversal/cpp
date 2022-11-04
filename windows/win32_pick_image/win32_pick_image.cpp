// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
#ifndef UNICODE
#define UNICODE
#endif

#include <stdint.h>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <algorithm>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ComDlg32.Lib")
#pragma comment(lib, "gdi32.lib")

#define IDM_MENU1 9001
#define IDM_MENU2 9002
#define IDM_MENU3 9003
#define WIDTH 256
#define HEIGHT 256

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HMENU hMenu = NULL;
HMENU mSubMenu = NULL;
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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
							LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			hMenu = CreateMenu();
			mSubMenu = CreateMenu();

			AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU1,
					   TEXT("Pick File"));
			AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU2,
					   TEXT("Window To uint8_t"));

			SetMenu(hWnd, hMenu);
		}
		case WM_COMMAND:
			switch (wParam) {
				case IDM_MENU1: {

					wchar_t szPath[MAX_PATH] = {};
					OPENFILENAME ofn = {
						sizeof(ofn)}; // common dialog box structure
					ofn.hwndOwner = hWnd;
					ofn.lpstrFilter = L"*.bmp";
					ofn.lpstrFile = szPath;
					ofn.nMaxFile = ARRAYSIZE(szPath);

					BOOL fOk = GetOpenFileName(&ofn);
					if (fOk) {
						HDC hdc = GetDC(hWnd);
						HDC hmemdc = CreateCompatibleDC(hdc);
						HBITMAP hBitmap = (HBITMAP)LoadImage(
							hInst, szPath, IMAGE_BITMAP, LR_DEFAULTSIZE,
							LR_DEFAULTSIZE, LR_LOADFROMFILE);
						if (hBitmap == NULL) {
							MessageBox(hWnd, L"load fail", L"error", MB_OK);
							break;
						}
						SelectObject(hmemdc, hBitmap);
						BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hmemdc, 0, 0, SRCCOPY);
						DeleteObject(hBitmap);
						ReleaseDC(hWnd, hmemdc);
					}
				} break;
				case IDM_MENU2: {
					// http://cn.voidcc.com/question/p-sdjnyeip-ns.html
					HDC hdc = GetDC(hWnd);
					HDC hdcMemoryDC = CreateCompatibleDC(hdc);

					BITMAPINFO bmi;
					memset(&bmi, 0, sizeof(BITMAPINFO));
					bmi.bmiHeader.biSize = sizeof(tagBITMAPINFOHEADER);
					bmi.bmiHeader.biWidth = WIDTH;
					bmi.bmiHeader.biHeight = -HEIGHT;
					bmi.bmiHeader.biPlanes = 1;
					bmi.bmiHeader.biBitCount = 32;
					bmi.bmiHeader.biCompression = BI_RGB;

					HBITMAP hbmp;
					COLORREF* pixelBuffer;
					hbmp = CreateDIBSection(hdcMemoryDC, &bmi, DIB_RGB_COLORS,
											(VOID**)&pixelBuffer, NULL, 0);
					SelectObject(hdcMemoryDC, hbmp);
					BitBlt(hdcMemoryDC, 0, 0, WIDTH, HEIGHT, hdc, 0, 0,
						   SRCCOPY);
					// https://stackoverflow.com/questions/65331211/what-is-the-size-of-ppvbits-returned-by-createdibsection
					size_t stride =
						((((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) +
						   31) &
						  ~31) >>
						 3);
					// BYTE r = GetRValue(pixelBuffer);
					// BYTE g = GetGValue(pixelBuffer);
					// BYTE b = GetBValue(pixelBuffer);

				} break;
				case IDM_MENU3: {
					uint32_t arr[240 * 120];
					std::fill(arr, arr + sizeof(arr) / sizeof(*arr),
							  RGB(255, 0, 0));
					// or std::fill(arr, arr + 240 * 120, RGB(255, 0, 0));
					HBITMAP hBitmap = CreateBitmap(240, 120, 1, 32, (void*)arr);
					MessageBox(hWnd, L"clicked menu3", L"alert", MB_OK);
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