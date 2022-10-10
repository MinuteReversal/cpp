// http://www.functionx.com/visualc/applications/simplewindow.htm
#include <afxwin.h>

class MainFrame : public CFrameWnd {
public:
  MainFrame() { Create(NULL, ""); }
};

class MainWindow : public CWinApp {
private:
  MainFrame *frame;

public:
  BOOL InitInstance() {
    frame = new MainFrame();
    m_pMainWnd = frame;

    m_pMainWnd->ShowWindow(SW_SHOW);
    frame->UpdateWindow();

    return TRUE;
  }
};

MainWindow wnd;
