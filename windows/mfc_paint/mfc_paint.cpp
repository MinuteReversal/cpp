#include <afxext.h>
#include <afxstr.h>
#include <afxwin.h>
#include <windef.h>
#include <winnt.h>

#pragma comment(linker, "/subsystem:windows")

class MainFrame : public CFrameWnd {
public:
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
};

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
ON_WM_CREATE()
ON_WM_PAINT()
END_MESSAGE_MAP()

void MainFrame::OnPaint() {
  CPaintDC dc(this);
  char text[] = "Hello World";
  CRect rect(0, 0, 0, 0);
  dc.DrawText(text, ARRAYSIZE(text) - 1, rect, DT_SINGLELINE | DT_NOCLIP);
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) { return 0; }

class MainWindow : public CWinApp {
private:
  MainFrame *frame;

public:
  virtual BOOL InitInstance() {
    frame = new MainFrame();
    // frame->LoadFrame(IDR_MAINFRAME);//must load frame resource??
    frame->Create(NULL, "MFC");
    m_pMainWnd = frame;

    frame->ShowWindow(SW_SHOW);
    frame->UpdateWindow();

    return TRUE;
  }
};

MainWindow wnd;