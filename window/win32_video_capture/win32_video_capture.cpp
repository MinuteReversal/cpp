// https://learn.microsoft.com/en-us/windows/win32/api/_multimedia/?source=recommendations
// https://learn.microsoft.com/en-us/windows/win32/multimedia/windows-multimedia-start-page?source=recommendations
// https://learn.microsoft.com/en-us/windows/win32/multimedia/windows-multimedia-start-page
// https://learn.microsoft.com/en-us/previous-versions/ms713463(v=vs.85)
#ifndef UNICODE
#define UNICODE

#include <corecrt_wstring.h>
#endif

#include <windows.h>
#include <Digitalv.h>
#include <vfw.h>
#include <joystickapi.h>
#include <mmddk.h>
#include <mmeapi.h>
#include <mmiscapi.h>
#include <mmreg.h>
#include <MSAcm.h>
#include <timeapi.h>
#include <wingdi.h>


#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "vfw32.lib")

#define IDC_CAPTURE_WINDOW 109
#define IDM_MENU_MAIN 40001
#define IDM_MENU_SCREENSHOT 40002
#define IDM_MENU_REFRESH 40003
#define IDM_MENU_SET_VIDEO 40004

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hWnd;
HBITMAP hBitmap = NULL;
HWND hWndC=NULL;

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
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();
    HMENU hDeviceMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Menu"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SCREENSHOT,
               TEXT("capture"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_REFRESH,
               TEXT("Refresh"));
    AppendMenu(hSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SET_VIDEO,
               TEXT("Set Video Charateristics"));

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hDeviceMenu, TEXT("Device"));

    hWndC = capCreateCaptureWindow(TEXT("My Capture Window"),
                                    WS_CHILD | WS_VISIBLE, 0, 0, 160, 120,
                                    hWnd, IDC_CAPTURE_WINDOW);
    LRESULT fOK = SendMessage (hWndC, WM_CAP_DRIVER_CONNECT, 0, 0L); 
      // 
      // Or, use the macro to connect to the MSVIDEO driver: 
      // fOK = capDriverConnect(hWndC, 0); 
      // 
      // Place code to set up and capture video here. 
      // 
      // capDriverDisconnect (hWndC); 

    wchar_t szDeviceName[80];
    wchar_t szDeviceVersion[80];

    for (int wIndex = 0; wIndex < 10; wIndex++) {
      if (capGetDriverDescription(wIndex, szDeviceName, sizeof(szDeviceName),
                                  szDeviceVersion, sizeof(szDeviceVersion))) {
        // Append name to list of installed capture drivers
        // and then let the user select a driver to use.
            AppendMenu(hDeviceMenu, MF_STRING, (UINT_PTR)9000+wIndex,
                szDeviceName);
      }
    }

    SetMenu(hWnd, hMenu);
  }
  case WM_COMMAND: {
    if (wParam == IDM_MENU_SCREENSHOT) {
      // https://stackoverflow.com/questions/3291167/how-can-i-take-a-screenshot-in-a-windows-application


      capPreviewRate(hWndC, 66); // rate, in milliseconds
      capPreview(hWndC, TRUE);   // starts preview

      // Preview

      capPreview(hWndC, FALSE);
      //InvalidateRect(hWnd, NULL, FALSE);
    } else if (wParam == IDM_MENU_SET_VIDEO) {
      
      HWND hWndC = capCreateCaptureWindow(TEXT("My Capture Window"),
    WS_CHILD | WS_VISIBLE, 0, 0, 160, 120, hWnd, IDC_CAPTURE_WINDOW);

    CAPDRIVERCAPS CapDriverCaps = { }; 
    CAPSTATUS     CapStatus = { };

    capDriverGetCaps(hWndC, &CapDriverCaps, sizeof(CAPDRIVERCAPS)); 
    
    // Video source dialog box. 
    if (CapDriverCaps.fHasDlgVideoSource)
    {
        capDlgVideoSource(hWndC); 
    }
    
    // Video format dialog box. 
    if (CapDriverCaps.fHasDlgVideoFormat) 
    {
        capDlgVideoFormat(hWndC); 

        // Are there new image dimensions?
        capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS));

        // If so, notify the parent of a size change.
    } 
    
    // Video display dialog box. 
    if (CapDriverCaps.fHasDlgVideoDisplay)
    {
        capDlgVideoDisplay(hWndC); 
    }

    CAPDRIVERCAPS CapDrvCaps; 

capDriverGetCaps(hWndC, &CapDrvCaps, sizeof (CAPDRIVERCAPS)); 

if (CapDrvCaps.fHasOverlay) 
    capOverlay(hWndC, TRUE);

    }
    else if (wParam == IDM_MENU_REFRESH) {
      // https://stackoverflow.com/questions/22277773/win32-content-changed-but-doesnt-show-update-unless-window-is-moved
      InvalidateRect(hWnd, NULL, FALSE);
    }
    else if(wParam==9000){
      SendMessage (hWndC, WM_CAP_DRIVER_CONNECT, 0, 0L); 
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

    if (hBitmap != NULL) {
      // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createpatternbrush
      HBRUSH pb = CreatePatternBrush(hBitmap);
      FillRect(hdc, &ps.rcPaint, pb);
    }

    EndPaint(hWnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}