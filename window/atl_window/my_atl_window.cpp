
#include "my_atl_window.h"
#include <windows.h>

#define IDC_MYATLWINDOWTEST 0x0001

HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
                     LPTSTR lpCmdLine, int nCmdShow) {
  MSG msg;
  hInst = hInstance;

  HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_MYATLWINDOWTEST));

  CMainWindow wnd;
  wnd.Create(NULL, CWindow::rcDefault, _T("My window"), WS_OVERLAPPEDWINDOW,
             WS_EX_CLIENTEDGE, hMenu);
  wnd.ShowWindow(nCmdShow);
  wnd.UpdateWindow();

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}
