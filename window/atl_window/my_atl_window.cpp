/**
 * @file my_atl_window.cpp
 * @author zhy (114233763@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 * http://t.zoukankan.com/liangxiaofeng-p-5066026.html
 */
#include "my_atl_window.h"
#include <windef.h>
#include <windows.h>
#include <winuser.h>


HINSTANCE hInstance;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
                     LPTSTR lpCmdLine, int nCmdShow) {
  MSG msg;
  hInstance = hInstance;

  HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(0x0001));

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