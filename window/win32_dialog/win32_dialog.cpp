#include <windows.h>
#include <winuser.h>

#pragma comment(lib, "user32.lib")

#define IDM_MENU_MAIN 40001
#define IDM_MENU_ALERT 40002
#define IDM_MENU_CONFIRM 40003
#define IDM_MENU_PROMPT 40004
#define IDD_PROMPT 50001

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR WINAPI DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_INITDIALOG:
    break;
  default:
    return FALSE;
  }
  return TRUE;
}

HWND hwnd;
HINSTANCE globalInstance;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const char CLASS_NAME[] = "Sample Window Class";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window.
  globalInstance = hInstance;
  hwnd = CreateWindow(            // Optional window styles.
      CLASS_NAME,                 // Window class
      "Learn to Program Windows", // Window text
      WS_OVERLAPPEDWINDOW,        // Window style

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
  case WM_CREATE: {
    HMENU hMenu = CreateMenu();
    HMENU mSubMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, "Menu");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_ALERT, "Alert");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_CONFIRM, "Confirm");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_PROMPT, "Prompt");
    SetMenu(hwnd, hMenu);
  }
    return 0;
  case WM_COMMAND: {
    if (wParam == IDM_MENU_ALERT) {
      MessageBox(hwnd, "your click sub menu", "alert", MB_OK);
    } else if (wParam == IDM_MENU_CONFIRM) {
      MessageBox(hwnd, "your click insert menu", "alert", MB_OKCANCEL);
    } else if (wParam == IDM_MENU_PROMPT) {
      DialogBoxParam(globalInstance, MAKEINTRESOURCE(IDD_PROMPT), hwnd,
                     DialogProc, lParam);
      DWORD err = GetLastError();
      if (err == ERROR_RESOURCE_DATA_NOT_FOUND) {
        MessageBox(hwnd, "ERROR_RESOURCE_DATA_NOT_FOUND", "error",
                   MB_OK | MB_ICONERROR);
      }
    }
  }
    return 0;
  case WM_INITDIALOG:

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