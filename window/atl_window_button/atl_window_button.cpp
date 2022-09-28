#include <atlbase.h>
#include <atlwin.h>
#include <minwindef.h>
#include <windef.h>
#include <windows.h>
#include <winuser.h>

#define IDC_MYATLWINDOWTEST 0x0001
#define IDC_Button_1 0x3301

class CMainWindow : public CWindowImpl<CMainWindow> {
private:
  HWND m_hButton1;

public:
  BEGIN_MSG_MAP(CMainWindow)
  COMMAND_ID_HANDLER(IDC_Button_1, OnButton1Click)
  MESSAGE_HANDLER(WM_CREATE, OnCreate)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MESSAGE_HANDLER(WM_DESTROY, OnDestory)
  END_MSG_MAP()

  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
    m_hButton1 = CreateWindow("BUTTON", // Predefined class; Unicode assumed
                               "OK",     // Button text
                               WS_TABSTOP | WS_VISIBLE | WS_CHILD |
                                   BS_DEFPUSHBUTTON, // Styles
                               0,                    // x position
                               0,                    // y position
                               120,                  // Button width
                               30,                   // Button height
                               m_hWnd,               // Parent window
                               (HMENU)IDC_Button_1,  // No menu.
                               (HINSTANCE)GetWindowLongPtr(GWLP_HINSTANCE),
                               NULL); // Pointer not needed.

    return 0;
  }

  LRESULT OnButton1Click(WORD wNotifyCode, WORD wID, HWND hWndCtl,
                         BOOL &bHandled) {
    MessageBox("click", "tip", MB_OK);
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