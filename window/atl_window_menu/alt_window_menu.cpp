#include <atlbase.h>
#include <atlwin.h>
#include <basetsd.h>
#include <windef.h>
#include <windows.h>
#include <winuser.h>

#define IDC_MYATLWINDOWTEST 0x0001
#define ID_SM 0x0002

class CMainWindow : public CWindowImpl<CMainWindow> {
private:
  HMENU m_hMenubar;
  HMENU m_hMenu;

public:
  BEGIN_MSG_MAP(CMainWindow)
  MESSAGE_HANDLER(WM_CREATE, OnCreate)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MESSAGE_HANDLER(WM_DESTROY, OnDestory)
  END_MSG_MAP()

  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    m_hMenubar = CreateMenu();
    m_hMenu = CreateMenu();
    AppendMenu(m_hMenubar, MF_POPUP, (UINT_PTR)m_hMenu, "Menu");
    AppendMenu(m_hMenu, MF_STRING, ID_SM, "Sub Menu");
    SetMenu(m_hMenubar);
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
  HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_MYATLWINDOWTEST));
  CMainWindow wnd;

  wnd.Create(NULL, CWindow::rcDefault, _T("Learn to Program Windows"),
             WS_OVERLAPPEDWINDOW, WS_EX_CLIENTEDGE, hMenu);
  wnd.ShowWindow(nCmdShow);
  wnd.UpdateWindow();

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}