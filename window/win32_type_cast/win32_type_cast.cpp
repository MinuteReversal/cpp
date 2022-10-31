// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
// https://learn.microsoft.com/zh-tw/cpp/text/how-to-convert-between-various-string-types?view=msvc-170#converting-between-narrow-and-wide-strings
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winuser.h>
#include <string.h>
#include "atlbase.h"
#include "atlstr.h"
#include <atlconv.h>

#define IDM_MENU1 9001
#define IDM_MENU2 9002
#define IDM_MENU3 9003

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HMENU hMenu = NULL;
HMENU mSubMenu = NULL;

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

  hWnd =
      CreateWindowEx(0,          // Optional window styles.
                     CLASS_NAME, // Window class
                     L"Learn Win32 To Program Windows", // Window text
                     WS_OVERLAPPEDWINDOW,               // Window style

                     // Size and position
                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

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
               TEXT("wchar* to char*"));
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU2,
               TEXT("char* to wchar*"));

    SetMenu(hWnd, hMenu);
  }
  case WM_COMMAND:
    switch (wParam) {
    case IDM_MENU1: {
      wchar_t szText[256] = {'\0'};
      wcscpy_s(szText, L"hello world\0"); // assignment =
      char* text = ATL::CW2A(szText);
      MessageBoxA(hWnd, text, "alert", MB_OK);
    } break;
    case IDM_MENU2: {
      // https://blog.csdn.net/RootSuper/article/details/55213180
      // https://learn.microsoft.com/zh-tw/cpp/c-runtime-library/reference/strncpy-s-strncpy-s-l-wcsncpy-s-wcsncpy-s-l-mbsncpy-s-mbsncpy-s-l?view=msvc-170
      char szText[256] = {};
      strncpy_s(szText, 256, "hello world\0", 12);
      wchar_t* text = ATL::CA2W(szText);
      MessageBoxW(hWnd, text, L"alert", MB_OK);
    } break;
    case IDM_MENU3:
      MessageBox(hWnd, L"clicked menu3", L"alert", MB_OK);
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