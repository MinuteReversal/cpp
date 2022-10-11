#include <afxwin.h>

class MainFrame : public CFrameWnd {
public:
  MainFrame() { Create(NULL, "Learn MFC To Program Windows"); }
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