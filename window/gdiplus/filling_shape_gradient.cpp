// https://docs.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-drawing-a-line-use

#ifndef UNICODE
#define UNICODE
#endif
#include "../base_window/base_window.h"
#include <gdiplus.h>
#include <objidl.h>
#include <windows.h>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

class MainWindow : public BaseWindow<MainWindow> {
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void OnPaint(HDC hdc);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;

  switch (uMsg) {
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
void MainWindow::OnPaint(HDC hdc) {
  Gdiplus::Graphics graphics(hdc);
  graphics.Clear(Color(255, 255, 255, 255));

  SolidBrush solidBrush(Color(255, 255, 0, 0));

  //画线
  Gdiplus::GraphicsPath path;
  LinearGradientBrush linGrBrush(Point(0, 10), Point(200, 10),
                                 Color(255, 255, 0, 0),  // opaque red
                                 Color(255, 0, 0, 255)); // opaque blue

  Pen pen(&linGrBrush);

  graphics.DrawLine(&pen, 0, 10, 200, 10);
  graphics.FillEllipse(&linGrBrush, 0, 30, 200, 100);
  graphics.FillRectangle(&linGrBrush, 0, 155, 500, 30);

  LinearGradientBrush linGrBrush2(Point(0, 10), Point(200, 10),
                                  Color(255, 0, 0, 0),    // opaque black
                                  Color(255, 255, 0, 0)); // opaque red

  REAL relativeIntensities[] = {0.0f, 0.5f, 1.0f};
  REAL relativePositions[] = {0.0f, 0.2f, 1.0f};

  linGrBrush2.SetBlend(relativeIntensities, relativePositions, 3);

  graphics.FillEllipse(&linGrBrush2, 0, 230, 200, 100);
  graphics.FillRectangle(&linGrBrush2, 0, 355, 500, 30);

  LinearGradientBrush linGrBrush3(Point(0, 0), Point(200, 100),
                                  Color(255, 0, 0, 255),  // opaque blue
                                  Color(255, 0, 255, 0)); // opaque green

  Pen pen3(&linGrBrush3, 10);

  graphics.DrawLine(&pen3, 0, 400, 600, 600);
  graphics.FillEllipse(&linGrBrush3, 10, 485, 200, 100);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine,
                   int nCmdShow) {
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
