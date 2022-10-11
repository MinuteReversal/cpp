#include "resource.h"
#include <windows.h>
#include <winuser.h>

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hwnd;
HINSTANCE globalInstance;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const char CLASS_NAME[] = "Win32";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
  wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
  

  RegisterClass(&wc);

  // Create the window.
  globalInstance = hInstance;
  hwnd = CreateWindow(     // Optional window styles.
      CLASS_NAME,          // Window class
      "Win32",      // Window text
      WS_OVERLAPPEDWINDOW, // Window style

      // Size and position
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

      NULL,      // Parent window
      NULL,      // Menu
      hInstance, // Instance handle
      NULL       // Additional application data
  );

  if (hwnd == NULL) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE:
    break;
  case WM_COMMAND:
    break;
  case WM_INITDIALOG:
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
    break;
  }
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}