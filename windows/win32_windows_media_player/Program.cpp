/*!
*****************************************************************************
* fileName    : Program.cpp
* author      : 114233763@qq.com
* date        : 2020-07-30 14:38:27
* version     : v1
* description :
* https://docs.microsoft.com/en-us/windows/win32/wmp/hosting-the-windows-media-player-control-in-a-windows-application
* https://stackoverflow.com/questions/1935964/basic-playback-with-programmatically-created-windows-media-player
* https://blog.csdn.net/JUNGOU1/article/details/7481355
***************************************************************************** */
#ifndef UNICODE
#define UNICODE
#include <atlcomcli.h>
#include <exception>
#include <excpt.h>
#include <minwindef.h>
#include <stdlib.h>
#include <windef.h>
#include <winerror.h>
#include <winuser.h>
#endif

#include "wmp.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlhost.h>
#include <stdexcept>
#include <windows.h>

HINSTANCE m_hInstance;        // application instance handle
HWND m_hWnd;                  // video frame window
CAxWindow m_wndView;          // ActiveX host window class.
CComBSTR bstrVersionInfo;     // Contains the version string.
CComPtr<IWMPPlayer> spPlayer; // Smart pointer to IWMPPlayer interface.
CComPtr<IWMPControls> controls;
CComPtr<IWMPPlaylist> playlist;
CComPtr<IAxWinHostWindow> spHost;

/**
 * @brief WindowProcedure
 *
 * @param hwnd
 * @param uMsg
 * @param wParam
 * @param lParam
 * @return LRESULT
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  LRESULT hResult = EXIT_SUCCESS;
  switch (uMsg) {
  case WM_INITDIALOG: {
    MessageBox(hwnd, L"hello", L"", NULL);
    break;
  }
  case WM_CREATE: {

    // CoInitialize(NULL);
    RECT rcClient = {0, 0, 400, 300};
    HRESULT hr = S_OK;

    // GetClientRect(m_hWnd, &rcClient);

    if (FALSE == AtlAxWinInit()) {
      MessageBox(hwnd, L"fail", L"error", MB_OK);
    }
    m_wndView.Create(m_hWnd, rcClient, NULL,
                     WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
    if (NULL == m_wndView.m_hWnd) {
      throw std::exception("create error");
    }
    // hr = spPlayer.CoCreateInstance(__uuidof(WindowsMediaPlayer), 0,
    //                                CLSCTX_INPROC_SERVER);

    hr = m_wndView.QueryHost(&spHost);

    if (SUCCEEDED(hr)) {
      hr = spHost->CreateControl(CComBSTR(__uuidof(WindowsMediaPlayer)),
                                 m_wndView, 0);
    }

    if (SUCCEEDED(hr)) {
      hr = m_wndView.QueryControl(&spPlayer);
    }

    if (SUCCEEDED(hr)) {
      hr = spPlayer->get_versionInfo(&bstrVersionInfo);
    }

    if (SUCCEEDED(hr)) {
      // Show the version in a message box.
      COLE2T pStr(bstrVersionInfo);
      MessageBox(NULL, pStr, _T("Windows Media Player Version"), MB_OK);
      spPlayer->get_controls(&controls);
      spPlayer->get_currentPlaylist(&playlist);

      CComBSTR path("D:\\mp4\\bee.mp4");
      spPlayer->put_URL(path);
      controls->play();
    }

    break;
  }
  case WM_DESTROY:
    // Clean up.
    // spPlayer.Release();
    // CoUninitialize();
    PostQuitMessage(0);
    break;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
    const wchar_t text[] = L"hello world";
    RECT rect;

    GetClientRect(hwnd, &rect);
    SetTextColor(hdc, RGB(0xFF, 0x00, 0x00));
    SetBkMode(hdc, TRANSPARENT);

    rect.left = 40;
    rect.top = 10;

    DrawText(hdc, text, ARRAYSIZE(text) - 1, &rect, DT_SINGLELINE | DT_NOCLIP);
    DeleteDC(hdc);
    EndPaint(hwnd, &ps);
    break;
  }
  default:
    hResult = DefWindowProc(hwnd, uMsg, wParam, lParam);
    break;
  }
  return hResult;
}

/**
 * @brief main
 *
 * @param hInstance
 * @param pCmdLine
 * @param nCmdShow
 * @return int
 */
int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
  m_hInstance = hInstance;
  // Register the window class.
  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window.
  HWND hwnd =
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
  if (hwnd == NULL) {
    return 0;
  }
  m_hWnd = hwnd;
  ShowWindow(hwnd, nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
