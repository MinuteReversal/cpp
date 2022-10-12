#include "resource.h"
#include <afxwin.h>

#pragma comment(linker, "/subsystem:windows")

class MainFrame : public CFrameWnd {
public:
  MainFrame() {}
};

class MainWindow : public CWinApp {
private:
  MainFrame *frame;

public:
  virtual BOOL InitInstance() {
    frame = new MainFrame();
    m_pMainWnd = frame;

    // frame->LoadFrame(IDR_MAINFRAME);// load resource
    frame->Create(NULL, "");
    frame->ShowWindow(SW_SHOW);
    frame->UpdateWindow();

    return TRUE;
  }
};

MainWindow wnd;