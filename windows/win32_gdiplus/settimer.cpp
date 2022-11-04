//https://docs.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
//https://docs.microsoft.com/en-us/windows/win32/gdi/drawing-at-timed-intervals

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#include "../base_window/base_window.h"
using namespace Gdiplus;
using namespace std;
#pragma comment(lib, "Gdiplus.lib")

#define IDT_TIMER1 1

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void OnPaint(HDC hdc, PAINTSTRUCT ps);

private:
  int count = 0;
};

/**
 * 画
 */
void MainWindow::OnPaint(HDC hdc, PAINTSTRUCT ps)
{
  Gdiplus::Graphics graphics(hdc);

  Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 255));
  Gdiplus::FontFamily fontFamily(L"Times New Roman");
  Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
  Gdiplus::PointF pointF(10.0f, 20.0f);
  graphics.Clear(Gdiplus::Color(255, 255, 255, 255)); //会闪烁

  count++;
  wstring msg = std::to_wstring(count);
  graphics.DrawString(msg.c_str(), -1, &font, pointF, &brush);
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  MSG msg = {};

  switch (uMsg)
  {
  case WM_CREATE:
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    SetTimer(m_hwnd, IDT_TIMER1, 1000, NULL);
    break;
  case WM_DESTROY:
    KillTimer(m_hwnd, IDT_TIMER1);
    Gdiplus::GdiplusShutdown(gdiplusToken);
    PostQuitMessage(0);
    break;
  case WM_PAINT:
    hdc = BeginPaint(m_hwnd, &ps);
    OnPaint(hdc, ps);
    EndPaint(m_hwnd, &ps);
    break;
  case WM_ERASEBKGND:

  case WM_TIMER:
    hdc = GetDC(m_hwnd);
    OnPaint(hdc, ps);
    break;
  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"SetTimer", WS_OVERLAPPEDWINDOW))
  {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
