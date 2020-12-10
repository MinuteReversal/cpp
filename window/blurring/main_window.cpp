//https://docs.microsoft.com/en-us/windows/win32/dwm/blur-ovw
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <dwmapi.h>
#include "../base_window/base_window.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_CLOSE:
    if (MessageBox(m_hwnd, L"Really quit?", ClassName(), MB_OKCANCEL) == IDOK)
    {
      DestroyWindow(m_hwnd);
    }
    return 0;
  case WM_PAINT:
  {
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

HRESULT ExtendIntoClientAll(HWND hwnd)
{
  HRESULT hr = S_OK;

  // Negative margins have special meaning to DwmExtendFrameIntoClientArea.
  // Negative margins create the "sheet of glass" effect, where the client
  // area is rendered as a solid surface without a window border.
  MARGINS margins = {-1};

  // Extend the frame across the whole window.
  hr = DwmExtendFrameIntoClientArea(hwnd, &margins);
  if (SUCCEEDED(hr))
  {
    // ...
  }
  return hr;
}

int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
  {
    return 0;
  }

  HWND w = win.Window();
  ExtendIntoClientAll(w);
  ShowWindow(w, nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
