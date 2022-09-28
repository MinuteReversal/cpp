/// https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-

#ifndef UNICODE
#define UNICODE
#endif
#include "../base_window/base_window.h"
#include <windows.h>


//依赖库
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

class MainWindow : public BaseWindow<MainWindow> {
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onPaint();
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
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
void MainWindow::onPaint() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);
  FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR pCmdLine, int nCmdShow) {
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
