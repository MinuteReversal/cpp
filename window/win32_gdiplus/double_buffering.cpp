//https://docs.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
//https://docs.microsoft.com/en-us/windows/win32/gdi/drawing-at-timed-intervals
//https://www.cnblogs.com/personnel/p/4585017.html

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <sstream>
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
  void OnPaint(HDC hdc);
  void DoubleBuffering(HDC hdc);
};

/**
 * 双线缓冲
 */
void MainWindow::DoubleBuffering(HDC hdc_old)
{
  //用于缓冲的内存DC

  HDC hdc = CreateCompatibleDC(hdc_old);
  //需要获取窗口的宽与高, 缓制尺寸
  RECT clientRect;
  GetClientRect(m_hwnd, &clientRect);
  //创建内存兼容位图hBmp
  HBITMAP hBmp = CreateCompatibleBitmap(hdc_old, clientRect.right, clientRect.bottom);
  //将内存位图选入缓冲内存DC中——以便可以绘制多个位图
  SelectObject(hdc, hBmp);
  //如果不执行这两步, 窗口显示出来会出现黑色背景
  //SelectObject(hdc, GetSysColorBrush(COLOR_3DFACE)); //设置刷子颜色 - Rectangle()的填充色
  //由于 Rectangle() 画出有黑色边框线, 这里故意从 -1,-1 绘制 +2, +2, 这样黑色边框线超出可视范围,就看不到了
  Rectangle(hdc, -1, -1, clientRect.right + 1, clientRect.bottom + 1); //画窗体的整个背景

  //调用绘画
  OnPaint(hdc);

  //将内存中的内容显示到窗口 - 使用bitblt函数
  BitBlt(hdc_old, 0, 0, clientRect.right, clientRect.bottom, hdc, 0, 0, SRCCOPY);
  //注意回收内存资源
  DeleteObject(hBmp);
  DeleteDC(hdc);
}

/**
 * 画
 */
void MainWindow::OnPaint(HDC hdc)
{

  Gdiplus::Graphics graphics(hdc);

  Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 255));
  Gdiplus::FontFamily fontFamily(L"Times New Roman");
  Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
  Gdiplus::PointF pointF(10.0f, 20.0f);

  SYSTEMTIME systemTime;
  GetLocalTime(&systemTime);

  std::wstringstream msg;
  msg << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond;
  graphics.DrawString(msg.str().c_str(), -1, &font, pointF, &brush);
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
    DoubleBuffering(hdc);
    EndPaint(m_hwnd, &ps);
    break;
  case WM_ERASEBKGND:
    return TRUE;
  case WM_TIMER:
    hdc = GetDC(m_hwnd);
    DoubleBuffering(hdc);
    break;
  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"Current Time", WS_OVERLAPPEDWINDOW))
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
