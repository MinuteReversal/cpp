#include <atlbase.h>
#include <atlwin.h>
#include <windows.h>

#define IDC_MYATLWINDOWTEST 0x0001

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
};

HINSTANCE hInst;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
                     LPTSTR lpCmdLine, int nCmdShow) {
  MSG msg;
  hInst = hInstance;

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