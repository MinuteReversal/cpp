// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
#ifndef UNICODE
#define UNICODE

#endif

#include <windows.h>
#include <wingdi.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define IDM_MENU_MAIN 40001
#define IDM_MENU_SCREENSHOT 40002
#define IDM_MENU_REFRESH 40003

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HBITMAP hBitmap = NULL;

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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    HMENU hMenu = CreateMenu();
    HMENU mSubMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SCREENSHOT,
               TEXT("ScreenShot"));
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_REFRESH,
               TEXT("Refresh"));

    SetMenu(hwnd, hMenu);
  }
  case WM_COMMAND: {
    if (wParam == IDM_MENU_SCREENSHOT) {
      // https://stackoverflow.com/questions/3291167/how-can-i-take-a-screenshot-in-a-windows-application
      HDC hScreenDC =
          GetDC(nullptr); // CreateDC("DISPLAY",nullptr,nullptr,nullptr);
      HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
      int width = GetDeviceCaps(hScreenDC, HORZRES);
      int height = GetDeviceCaps(hScreenDC, VERTRES);
      hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
      HBITMAP hOldBitmap =
          static_cast<HBITMAP>(SelectObject(hMemoryDC, hBitmap));
      BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
      hBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hOldBitmap));
      DeleteDC(hMemoryDC);
      DeleteDC(hScreenDC);
      InvalidateRect(hWnd, NULL, FALSE);
    } else if (wParam == IDM_MENU_REFRESH) {
      //https://stackoverflow.com/questions/22277773/win32-content-changed-but-doesnt-show-update-unless-window-is-moved
      InvalidateRect(hWnd, NULL, FALSE);
    }
  }
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    if (hBitmap != NULL) {
      // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createpatternbrush
      HBRUSH pb = CreatePatternBrush(hBitmap);
      FillRect(hdc, &ps.rcPaint, pb);
    }

    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}