#include "resource.h"
#include <windows.h>
#include <winuser.h>

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hwnd = NULL;
HINSTANCE g_hInstance = NULL;
HWND g_hToolbar = NULL;

INT_PTR CALLBACK ToolDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam) {
  switch (uMsg) {
  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case IDC_PRESS:
      MessageBox(hwnd, "Hi", "This is message", MB_OK | MB_ICONEXCLAMATION);
      break;
    case IDC_OTHER:
      MessageBox(hwnd, "Bye!", "This is also a message",
                 MB_OK | MB_ICONEXCLAMATION);
      break;
    }
  default:
    return FALSE;
  }
  return TRUE;
}

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
  g_hInstance = hInstance;
  hwnd = CreateWindow(                  // Optional window styles.
      CLASS_NAME,                       // Window class
      "Learn Win32 To Program Windows", // Window text
      WS_OVERLAPPEDWINDOW,              // Window style

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
  case WM_COMMAND:
    switch (wParam) {
    case ID_FILE_EXIT:
      PostMessage(hwnd, WM_CLOSE, 0, 0);
      break;
    case ID_MENU_SHOW:
      ShowWindow(g_hToolbar, SW_SHOW);
      break;
    case ID_MENU_HIDE:
      ShowWindow(g_hToolbar, SW_HIDE);
      break;
    }
    break;
  case WM_CREATE:
    g_hToolbar = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_TOOLBAR), hwnd,
                              ToolDlgProc);
    if (g_hToolbar != NULL) {
      ShowWindow(g_hToolbar, SW_SHOW);
    } else {
      MessageBox(hwnd, "CreateDialog returned NULL", "Warning!",
                 MB_OK | MB_ICONINFORMATION);
    }
    break;
  case WM_INITDIALOG:
    break;
  case WM_DESTROY:
    DestroyWindow(g_hToolbar);
    PostQuitMessage(0);
    break;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
    break;
  }
  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}