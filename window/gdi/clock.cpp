//https://docs.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
//https://docs.microsoft.com/en-us/windows/win32/gdi/drawing-at-timed-intervals
//https://www.cnblogs.com/personnel/p/4585017.html

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <objidl.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include "../base_window/base_window.h"

#define IDT_TIMER1 1

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void DoubleBuffering(HDC hdc);
  void OnPaint(HDC hdc);
  void DrawClockFace(HDC hdc);
  void DrawHand(HDC hdc, int nLength, int nWidth, int nDegrees, COLORREF clrColor);

private:
  PAINTSTRUCT ps;
  double offsetTop;
  double offsetLeft;
  void CalcCenter();
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
  DrawClockFace(hdc);

  SYSTEMTIME time;
  GetLocalTime(&time);
  double m = time.wMinute / 60.0;
  double s = time.wSecond / 60.0;
  DrawHand(hdc, 100, 8, (time.wHour + m) / 12.0 * 360, COLORREF(0x00000000));
  DrawHand(hdc, 120, 6, (time.wMinute + s) / 60.0 * 360, COLORREF(0x00000000));
  DrawHand(hdc, 150, 1, s * 360, COLORREF(0x000000FF));
}

/**
 * 画表盘
 */
void MainWindow::DrawClockFace(HDC hdc)
{
  const int HALFSIZE = 10;
  const int RADIUS = 200;
  SelectObject(hdc, GetStockObject(BLACK_BRUSH));
  for (size_t i = 0; i < 12; i++)
  {
    double nRadians = 360 / 12 * i * 0.0174533;
    int x = (int)(RADIUS * sin(nRadians));
    int y = (int)(RADIUS * cos(nRadians));
    Ellipse(hdc, offsetLeft + x - HALFSIZE, offsetTop + y - HALFSIZE, offsetLeft + x + HALFSIZE, offsetTop + y + HALFSIZE);
  }
}

/**
 * 画指针
 */
void MainWindow::DrawHand(HDC hdc, int nLength, int nWidth, int nDegrees, COLORREF clrColor)
{
  double nRadians = (180 - nDegrees) * 0.0174533;
  POINT pt[2];
  pt[0].x = (int)(nLength * sin(nRadians));
  pt[0].y = (int)(nLength * cos(nRadians));
  pt[1].x = -pt[0].x / 5;
  pt[1].y = -pt[0].y / 5;

  HPEN hPen = CreatePen(PS_SOLID, nWidth, clrColor);
  HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
  MoveToEx(hdc, offsetLeft + pt[0].x, offsetTop + pt[0].y, NULL);
  LineTo(hdc, offsetLeft + pt[1].x, offsetTop + pt[1].y);
  SelectObject(hdc, hOldPen);
  DeleteObject(hPen);
}

void MainWindow::CalcCenter()
{
  offsetLeft = ps.rcPaint.right / 2;
  offsetTop = ps.rcPaint.bottom / 2;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

  HDC hdc;
  MSG msg = {};

  switch (uMsg)
  {
  case WM_CREATE:
    SetTimer(m_hwnd, IDT_TIMER1, 1000, NULL);
    break;
  case WM_DESTROY:
    KillTimer(m_hwnd, IDT_TIMER1);
    PostQuitMessage(0);
    break;
  case WM_PAINT:
    hdc = BeginPaint(m_hwnd, &ps);
    CalcCenter();
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
