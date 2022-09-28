#include "atlbase.h"
#include "atlwin.h"
#include <windows.h>
#include <stdlib.h>
#include <windef.h>
#include <winuser.h>

#define IDD_ABOUTBOX 0x0001

class CMainWindow : public CWindowImpl<CMainWindow> {
public:
  BEGIN_MSG_MAP(CMainWindow)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MESSAGE_HANDLER(WM_DESTROY, OnDestory)
  END_MSG_MAP()
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
  LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled) {
    CSimpleDialog<IDD_ABOUTBOX> dlg;
    dlg.DoModal();
    return 0;
  }
};