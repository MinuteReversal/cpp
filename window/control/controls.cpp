//https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
//http://www.cplusplus.com/forum/windows/90014/
//http://www.cplusplus.com/forum/windows/11305/
//https://stackoverflow.com/questions/37271194/wm-command-catch-button-press-in-c-win32

#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include "../base_window/base_window.h"

#define IDC_BUTTON_1 0x1
#define IDC_BUTTON_2 0x2

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  void onCreate();
  void onPaint();
  void Button1_OnClick();
  HWND button1;
  HWND button2;
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    if (LOWORD(wParam) == IDC_BUTTON_1)
    {
      Button1_OnClick();
    }
    return 0;
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

void MainWindow::Button1_OnClick()
{
  MessageBox(m_hwnd, L"clicked", L"title", MB_OK);
}

void MainWindow::onCreate()
{
  //
  //按钮
  button1 = CreateWindow(
      L"BUTTON",                                             // Predefined class; Unicode assumed
      L"OK",                                                 // Button text
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
      10,                                                    // x position
      10,                                                    // y position
      100,                                                   // Button width
      100,                                                   // Button height
      m_hwnd,                                                // Parent window
      (HMENU)IDC_BUTTON_1,                                   // For a child window, hMenu specifies the child-window identifier.
      (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
      NULL);

  button2 = CreateWindow(
      L"BUTTON",                                             // Predefined class; Unicode assumed
      L"OK2",                                                // Button text
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
      120,                                                   // x position
      10,                                                    // y position
      100,                                                   // Button width
      100,                                                   // Button height
      m_hwnd,                                                // Parent window
      (HMENU)IDC_BUTTON_2,                                   // No menu.
      (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
      NULL);
}

/**
 * 画线
 */
void MainWindow::onPaint()
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);
  FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
  EndPaint(m_hwnd, &ps);
}

/**
 * 入口
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
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
