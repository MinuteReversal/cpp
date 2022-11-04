//https://docs.microsoft.com/en-us/windows/win32/dwm/blur-ovw
//https://tieba.baidu.com/p/6455993677
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <gdiplus.h>
#include <dwmapi.h>
#include "../base_window/base_window.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  HRESULT Blur(HWND hwnd);
  void onPaint();
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    Blur(m_hwnd);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_CLOSE:
    DestroyWindow(m_hwnd);
    return 0;
  case WM_PAINT:
    onPaint();
    return 0;
  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return TRUE;
}
/**
 * 画线
 */
void MainWindow::onPaint()
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);
  // FillRect(hdc, &ps.rcPaint, (HBRUSH)(BLACK_BRUSH));

  //画线
  HPEN hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
  SelectObject(hdc, hPen);
  MoveToEx(hdc, 0, 00, (LPPOINT)NULL);
  LineTo(hdc, 200, 200);

  //弧
  Arc(hdc, 0, 200, 200, 400, 0, 200, 200, 400);

  //弧
  ArcTo(hdc, 200, 200, 400, 400, 200, 200, 400, 400);

  //圆
  Ellipse(hdc, 200, 0, 400, 200);

  //矩形
  Rectangle(hdc, 400, 0, 600, 200);

  EndPaint(m_hwnd, &ps);
}

HRESULT MainWindow::Blur(HWND hwnd)
{
  HRESULT hr = S_OK;

  // Create and populate the Blur Behind structure
  DWM_BLURBEHIND bb = {};

  // Enable Blur Behind and apply to the entire client area
  bb.dwFlags = DWM_BB_ENABLE;
  bb.fEnable = true;
  bb.hRgnBlur = NULL;

  // Apply Blur Behind
  hr = DwmEnableBlurBehindWindow(hwnd, &bb);
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
