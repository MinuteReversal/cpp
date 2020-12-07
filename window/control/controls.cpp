///https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include "../base_window/base_window.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
  void onCreate();
  void onPaint();
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    onCreate();
    return 0;
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

void MainWindow::onCreate()
{
  //按钮
  HWND hwndButton = CreateWindow(
      L"BUTTON",                                             // Predefined class; Unicode assumed
      L"OK",                                                 // Button text
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
      10,                                                    // x position
      10,                                                    // y position
      100,                                                   // Button width
      100,                                                   // Button height
      m_hwnd,                                                // Parent window
      NULL,                                                  // No menu.
      (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
      NULL);
}

/**
 * 画线
 */
void MainWindow::onPaint()
{
}

/**
 * 入口
 */
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
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
