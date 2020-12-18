//http://www.cplusplus.com/forum/windows/86175/

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
  //---
  MoveToEx(hdc, 60, 20, NULL);

  LineTo(hdc, 90, 20);
  LineTo(hdc, 90, 50);
  LineTo(hdc, 60, 50);
  LineTo(hdc, 60, 20);

  MoveToEx(hdc, 80, 40, NULL);

  LineTo(hdc, 110, 40);
  LineTo(hdc, 110, 70);
  LineTo(hdc, 80, 70);
  LineTo(hdc, 80, 40);

  MoveToEx(hdc, 60, 20, NULL);
  LineTo(hdc, 80, 40);
  MoveToEx(hdc, 90, 20, NULL);
  LineTo(hdc, 110, 40);
  MoveToEx(hdc, 60, 50, NULL);
  LineTo(hdc, 80, 70);
  MoveToEx(hdc, 90, 50, NULL);
  LineTo(hdc, 110, 70);
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

  HDC hdc;
  MSG msg = {};

  switch (uMsg)
  {
  case WM_CREATE:
    //SetTimer(m_hwnd, IDT_TIMER1, 1000, NULL);
    break;
  case WM_DESTROY:
    KillTimer(m_hwnd, IDT_TIMER1);
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

  if (!win.Create(L"cube", WS_OVERLAPPEDWINDOW))
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
