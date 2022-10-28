// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winuser.h>

#define IDC_MFPLAYBACK 109
#define IDM_MENU_MAIN 40001
#define IDM_MENU_SUB 40002
#define IDM_MENU_INSERT 40003

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND hWnd;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.lpszMenuName = MAKEINTRESOURCE(IDC_MFPLAYBACK);

  RegisterClass(&wc);

  // Create the window.

  hWnd =
      CreateWindowEx(0,                           // Optional window styles.
                     CLASS_NAME,                  // Window class
                     L"Learn to Program Windows", // Window text
                     WS_OVERLAPPEDWINDOW,         // Window style

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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    HMENU hMenu = CreateMenu();
    HMENU mSubMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SUB, TEXT("Sub Menu"));
    InsertMenu(mSubMenu, 0, MF_STRING, (UINT_PTR)IDM_MENU_INSERT,
               TEXT("Insert at 0"));

    SetMenu(hwnd, hMenu);
  }
    return 0;
  case WM_COMMAND: {
    if (wParam == IDM_MENU_SUB) {
      MessageBox(hwnd, L"your click sub menu", L"alert", MB_OK);
    } else if (wParam == IDM_MENU_INSERT) {
      MessageBox(hwnd, L"your click insert menu", L"alert", MB_OK);
    }
  }
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint.

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}