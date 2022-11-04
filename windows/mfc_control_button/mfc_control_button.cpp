#include <afxext.h>
#include <afxwin.h>

#pragma comment(linker, "/subsystem:windows")

#define IDC_BUTTON1 4001

class MainFrame : public CFrameWnd {
protected:
  CButton button1;

public:
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg void OnButton1Click();
};

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
ON_WM_CREATE()
ON_WM_PAINT()
ON_COMMAND(IDC_BUTTON1, &MainFrame::OnButton1Click)

END_MESSAGE_MAP()

void MainFrame::OnPaint() { CPaintDC dc(this); }

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  button1.Create("button1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 CRect(0, 0, 120, 30), this, IDC_BUTTON1);
  return 0;
}

void MainFrame::OnButton1Click() {
  MessageBox("button1 clicked", "", MB_OK);
}

class MainWindow : public CWinApp {
private:
  MainFrame *frame;

public:
  virtual BOOL InitInstance() {
    frame = new MainFrame();
    m_pMainWnd = frame;
    frame->Create(NULL, "");
    frame->ShowWindow(SW_SHOW);
    frame->UpdateWindow();

    return TRUE;
  }
};

MainWindow wnd;