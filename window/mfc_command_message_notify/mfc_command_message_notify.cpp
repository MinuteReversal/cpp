// https://learn.microsoft.com/zh-tw/cpp/mfc/reference/clistctrl-class?view=msvc-170#clistctrl
// https://learn.microsoft.com/en-us/cpp/mfc/tn061-on-notify-and-wm-notify-messages?view=msvc-170
#include "resource.h"
#include <afxcmn.h>
#include <afxext.h>
#include <afxwin.h>

#pragma comment(linker, "/subsystem:windows")

class MainFrame : public CFrameWnd {
protected:
  CButton button1;
  CListCtrl list1;

public:
  DECLARE_MESSAGE_MAP() afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg void OnButton1Click();
  afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
  afx_msg void OnMyKeydown(NMHDR *pNMHDR, LRESULT *pResult);
};

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
ON_WM_CREATE()
ON_WM_PAINT()
ON_COMMAND(IDC_BUTTON1, &MainFrame::OnButton1Click)
ON_MESSAGE(WM_MYMESSAGE, &MainFrame::OnMyMessage)
ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &MainFrame::OnMyKeydown)
END_MESSAGE_MAP()

void MainFrame::OnPaint() { CPaintDC dc(this); }

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  button1.Create("button1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 CRect(0, 0, 120, 30), this, IDC_BUTTON1);
  list1.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
               CRect(0, 30, 400, 200), this, IDC_LIST1);
  return 0;
}

void MainFrame::OnButton1Click() {
  MessageBox("button1 clicked", "", MB_OK);
  PostMessage(WM_MYMESSAGE); // dispatch message
}

LRESULT MainFrame::OnMyMessage(WPARAM wParam, LPARAM lParam) {
  MessageBox("get message", "", MB_OK);
  return 0;
}

void MainFrame::OnMyKeydown(NMHDR *pNMHDR, LRESULT *pResult) {
  MessageBox("key down", "", MB_OK);
  LV_KEYDOWN *pLVKEYDOWN = (LV_KEYDOWN *)pNMHDR;

  *pResult = 0;
}

class MainWindow : public CWinApp {
private:
  MainFrame *frame;

public:
  virtual BOOL InitInstance() {
    frame = new MainFrame();
    m_pMainWnd = frame;
    frame->LoadFrame(IDR_MAINFRAME);
    frame->ShowWindow(SW_SHOW);
    frame->UpdateWindow();

    return TRUE;
  }
};

MainWindow wnd;