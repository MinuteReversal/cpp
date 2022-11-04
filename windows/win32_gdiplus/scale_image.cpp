//https://docs.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-using-images-bitmaps-and-metafiles-use

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

  Image image(L"D:\\code\\CPlusPlus\\cpp\\window\\gdiplus\\images\\Apple.gif");
  UINT width = image.GetWidth();
  UINT height = image.GetHeight();
  // Make the destination rectangle 30 percent wider and
  // 30 percent taller than the original image.
  // Put the upper-left corner of the destination
  // rectangle at (150, 20).
  Rect destinationRect(150, 20, 1.3 * width, 1.3 * height);
  // Draw the image unaltered with its upper-left corner at (0, 0).
  graphics.DrawImage(&image, 0, 0);
  // Draw a portion of the image. Scale that portion of the image
  // so that it fills the destination rectangle.
  graphics.DrawImage(
      &image,
      destinationRect,
      0, 0,          // upper-left corner of source rectangle
      0.75 * width,  // width of source rectangle
      0.75 * height, // height of source rectangle
      UnitPixel);
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
