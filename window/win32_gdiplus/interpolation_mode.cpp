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

  Gdiplus::Image image(L"D:\\code\\CPlusPlus\\cpp\\window\\gdiplus\\images\\GrapeBunch.bmp");
  UINT width = image.GetWidth();
  UINT height = image.GetHeight();
  // Draw the image with no shrinking or stretching.
  graphics.DrawImage(
      &image,
      Rect(10, 10, width, height), // destination rectangle
      0, 0,                        // upper-left corner of source rectangle
      width,                       // width of source rectangle
      height,                      // height of source rectangle
      UnitPixel);
  // Shrink the image using low-quality interpolation.
  graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
  graphics.DrawImage(
      &image,
      Rect(10, 250, 0.6 * width, 0.6 * height), // destination rectangle
      0, 0,                                     // upper-left corner of source rectangle
      width,                                    // width of source rectangle
      height,                                   // height of source rectangle
      UnitPixel);
  // Shrink the image using medium-quality interpolation.
  graphics.SetInterpolationMode(InterpolationModeHighQualityBilinear);
  graphics.DrawImage(
      &image,
      Rect(150, 250, 0.6 * width, 0.6 * height), // destination rectangle
      0, 0,                                      // upper-left corner of source rectangle
      width,                                     // width of source rectangle
      height,                                    // height of source rectangle
      UnitPixel);
  // Shrink the image using high-quality interpolation.
  graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
  graphics.DrawImage(
      &image,
      Rect(290, 250, 0.6 * width, 0.6 * height), // destination rectangle
      0, 0,                                      // upper-left corner of source rectangle
      width,                                     // width of source rectangle
      height,                                    // height of source rectangle
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
