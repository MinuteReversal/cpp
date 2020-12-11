//https://docs.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-drawing-a-line-use

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "../base_window/base_window.h"
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void OnPaint(HDC hdc);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;

  switch (uMsg)
  {
  case WM_CREATE:
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    break;
  case WM_DESTROY:
    GdiplusShutdown(gdiplusToken);
    PostQuitMessage(0);
    break;
  case WM_PAINT:
    hdc = BeginPaint(m_hwnd, &ps);
    OnPaint(hdc);
    EndPaint(m_hwnd, &ps);
    break;
  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return FALSE;
}

/**
 * 画
 */
void MainWindow::OnPaint(HDC hdc)
{
  Gdiplus::Graphics graphics(hdc);

  SolidBrush solidBrush(Color(255, 255, 0, 0));

  //画线
  Gdiplus::GraphicsPath path;
  path.StartFigure();
  path.AddLine(Gdiplus::Point(0, 0), Gdiplus::Point(200, 50));
  path.AddLine(Gdiplus::Point(200, 50), Gdiplus::Point(0, 100));

  //填充路径
  graphics.FillPath(&solidBrush, &path);

  //填充方块
  graphics.FillRectangle(&solidBrush, 200, 0, 100, 100);

  //填充椭圆
  graphics.FillEllipse(&solidBrush, 300, 0, 100, 100);

  //填充饼
  graphics.FillPie(&solidBrush, 400, 0, 100, 100, 0, 90);

  //填充曲线
  Gdiplus::Point points[] = {Gdiplus::Point(500, 0), Gdiplus::Point(600, 100), Gdiplus::Point(700, 0)};
  graphics.FillClosedCurve(&solidBrush, points, ARRAYSIZE(points));

  //多边形
  Gdiplus::Point points2[] = {Gdiplus::Point(700, 0), Gdiplus::Point(800, 100), Gdiplus::Point(900, 0)};
  graphics.FillPolygon(&solidBrush, points2, ARRAYSIZE(points2));

  //区域
  Gdiplus::Region region(Gdiplus::Rect(0, 100, 100, 100));
  graphics.FillRegion(&solidBrush, &region);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
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
