#ifndef UNICODE
#define UNICODE
#endif
#include "../base_window/base_window.h"
#include <windows.h>

#define IDC_STATIC 0x1

class MainWindow : public BaseWindow<MainWindow> {
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  HWND g_myStatic;
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE:
    // g_myStatic is a global HWND variable.
    g_myStatic = CreateWindowEx(0, L"STATIC", L"Some static text",
                                WS_CHILD | WS_VISIBLE | SS_OWNERDRAW, 25, 125,
                                150, 20, m_hwnd, 0, 0, 0);
    return 0;
  case WM_DRAWITEM: {
    LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
    if (pDIS->hwndItem == g_myStatic) {
      SetTextColor(pDIS->hDC, RGB(100, 0, 100));
      wchar_t staticText[99];
      //获取指定hwnd的标题
      int len = SendMessage(g_myStatic, WM_GETTEXT,
                            (sizeof(staticText) / sizeof(wchar_t)),
                            (LPARAM)staticText);
      TextOut(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, staticText, len);
    }
  }
    return TRUE;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_CLOSE:
    DestroyWindow(m_hwnd);
    return 0;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(m_hwnd, &ps);
  }
    return 0;
  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return TRUE;
}

int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
  MainWindow win;

  if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW)) {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
