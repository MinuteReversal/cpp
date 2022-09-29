//[](http://t.zoukankan.com/liangxiaofeng-p-5066026.html)
#include "atlbase.h"
#include "atlwin.h"
#include <minwindef.h>
#include <stdlib.h>
#include <windef.h>
#include <windows.h>
#include <winnt.h>
#include <winuser.h>

#define IDM_ABOUT     0x0001
#define IDM_EXIT      0x0002
#define IDD_ABOUTBOX  0x0003

class CMainWindow : public CWindowImpl<CMainWindow> {
public:
  BEGIN_MSG_MAP(CMainWindow)
  COMMAND_ID_HANDLER(IDM_ABOUT, OnAbout)
  COMMAND_ID_HANDLER(IDM_EXIT, OnExit)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MESSAGE_HANDLER(WM_DESTROY, OnDestory)
  END_MSG_MAP()

  LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam,
                       BOOL &bHandled) {
    return 0;
  }

  LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    PAINTSTRUCT ps;
    this->BeginPaint(&ps);
    char str[] = "hello world";
    RECT rc;
    rc.top = 0;
    rc.left = 0;
    DrawText(ps.hdc, str, ARRAYSIZE(str) - 1, &rc, DT_SINGLELINE | DT_NOCLIP);
    this->EndPaint(&ps);
    return 0;
  }

  LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    PostQuitMessage(0);
    return 0;
  }

  LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled) {
    CSimpleDialog<IDD_ABOUTBOX> dlg;
    dlg.DoModal();
    return 0;
  }

  LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled) {
    this->DestroyWindow();
    return 0;
  }
};