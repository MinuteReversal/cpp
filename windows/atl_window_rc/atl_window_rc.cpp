#include "resource.h"
#include <afx.h>
#include <atlbase.h>
#include <atlwin.h>
#include <windows.h>
#include <winuser.h>

class CMainWindow : public CWindowImpl<CMainWindow> {
public:
  BEGIN_MSG_MAP(CMainWindow)
  MESSAGE_HANDLER(WM_CREATE, OnCreate)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MESSAGE_HANDLER(WM_DESTROY, OnDestory)
  END_MSG_MAP()

  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    return 0;
  }

  LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    PAINTSTRUCT ps;
    this->BeginPaint(&ps);
    this->EndPaint(&ps);
    return 0;
  }

  LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    PostQuitMessage(0);
    return 0;
  }
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
                     LPTSTR lpCmdLine, int nCmdShow) {
  MSG msg;
  HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MYMENU));
  HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
  CMainWindow wnd;

  wnd.Create(NULL, CWindow::rcDefault, _T("Learn to Program Windows"),
             WS_OVERLAPPEDWINDOW, WS_EX_CLIENTEDGE, hMenu);
  wnd.SetIcon(hIcon);
  wnd.ShowWindow(nCmdShow);
  wnd.UpdateWindow();

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}