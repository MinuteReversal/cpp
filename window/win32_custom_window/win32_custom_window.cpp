// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HWND hDlg;

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
  case WM_CREATE:
    // g_myStatic is a global HWND variable.
    hDlg = CreateWindowEx(0, L"STATIC", L"Some static text",
                          WS_CHILD | WS_VISIBLE | SS_OWNERDRAW, 25, 125, 150,
                          20, hWnd, 0, 0, 0);
    return 0;
  case WM_DRAWITEM: {
    LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
    if (pDIS->hwndItem == hDlg) {
      SetTextColor(pDIS->hDC, RGB(100, 0, 100));
      wchar_t staticText[99];
      // 获取指定hwnd的标题
      int len =
          SendMessage(hDlg, WM_GETTEXT, (sizeof(staticText) / sizeof(wchar_t)),
                      (LPARAM)staticText);
      TextOut(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, staticText, len);
    }
  }
    return TRUE;
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