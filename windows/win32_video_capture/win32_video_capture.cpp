// https://learn.microsoft.com/en-us/windows/win32/api/_multimedia/?source=recommendations
// https://learn.microsoft.com/en-us/windows/win32/multimedia/windows-multimedia-start-page?source=recommendations
// https://learn.microsoft.com/en-us/windows/win32/multimedia/windows-multimedia-start-page
// https://learn.microsoft.com/en-us/previous-versions/ms713463(v=vs.85)
// https://www.cnblogs.com/ciano/p/3446417.html
// clang-format off
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <cassert>
#include <digitalv.h>
#include <vfw.h>
#include <joystickapi.h>
#include <mmddk.h>
#include <mmeapi.h>
#include <mmiscapi.h>
#include <mmreg.h>
#include <msacm.h>
#include <timeapi.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "vfw32.lib")
// clang-format on

#define IDC_CAPTURE_WINDOW 109
#define IDM_MENU_MAIN 40001
#define IDM_MENU_CONNECT 40002
#define IDM_MENU_DISCONNECT 40003
#define IDM_MENU_CAPTURE 40004
#define IDM_MENU_SAVE 40005

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInstance = NULL;
HWND hWnd = NULL;
HWND hWndC = NULL;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      PWSTR pCmdLine, int nCmdShow) {
  g_hInstance = hInstance;
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
    // create menu
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();
    HMENU hDeviceMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Menu"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_CAPTURE,
               TEXT("Capture"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_CONNECT,
               TEXT("Connect"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_DISCONNECT,
               TEXT("Disconnect"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SAVE, TEXT("Save"));

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hDeviceMenu, TEXT("Device"));

    wchar_t szDeviceName[80];
    wchar_t szDeviceVersion[80];

    for (int wIndex = 0; wIndex < 10; wIndex++) {
      if (capGetDriverDescription(wIndex, szDeviceName, sizeof(szDeviceName),
                                  szDeviceVersion, sizeof(szDeviceVersion))) {
        // Append name to list of installed capture drivers
        // and then let the user select a driver to use.
        AppendMenu(hDeviceMenu, MF_STRING, (UINT_PTR)9000 + wIndex,
                   szDeviceName);
      }
    }
    SetMenu(hWnd, hMenu);

    // create preview window
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    hWndC = capCreateCaptureWindow(
        TEXT("My Capture Window"), WS_CHILD | WS_VISIBLE, 0, 0,
        clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
        hWnd, IDC_CAPTURE_WINDOW);
  }
  case WM_COMMAND: {
    if (wParam == IDM_MENU_CONNECT) {
      // hIsConnected = SendMessage(hWndC, WM_CAP_DRIVER_CONNECT, 0, 0L);
      // Or, use the macro to connect to the MSVIDEO driver:
      assert(NULL != hWndC);
      capDriverConnect(hWndC, 0);
      capPreviewRate(hWndC, 60);
      capPreview(hWndC, TRUE);
    } else if (wParam == IDM_MENU_DISCONNECT) {
      assert(NULL != hWndC);
      capPreview(hWndC, FALSE);
      capDriverDisconnect(hWndC);
    } else if (wParam == IDM_MENU_CAPTURE) {
      assert(NULL != hWndC);
      char szCaptureFile[] = "MYCAP.AVI";
      capFileSetCaptureFile(hWndC, szCaptureFile);
      capFileAlloc(hWndC, (1024L * 1024L * 5));
      // capFileSaveAs(hWndC, szCaptureFile);
    } else if (wParam == IDM_MENU_SAVE) {
      assert(NULL != hWndC);
      char szCaptureFile[] = "MYCAP.AVI";
      capCaptureSequence(hWndC);
      capFileSaveAs(hWndC, szCaptureFile);
    }
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