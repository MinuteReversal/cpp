// https://stackoverflow.com/questions/60183665/mfc-using-chtmlview-with-memory-string-via-about-or-data
#include <afxext.h>
#include <afxhtml.h>
#include <afxstr.h>
#include <afxwin.h>

#pragma comment(linker, "/subsystem:windows")

#define IDC_HTML 4001

class HtmlView : public CHtmlEditView {
public:
  void Load(CString strHtml);

protected:
  DECLARE_MESSAGE_MAP()
  virtual void PostNcDestroy();
  afx_msg void OnDestroy();
};
BEGIN_MESSAGE_MAP(HtmlView, CHtmlEditView)
ON_WM_DESTROY()

END_MESSAGE_MAP()

void HtmlView::OnDestroy() {
  m_pBrowserApp.Release();
  m_pBrowserApp = NULL;
  CWnd::OnDestroy();
}

void HtmlView::PostNcDestroy() {
  // CHtmlView::PostNcDestroy();
}

void HtmlView::Load(CString html) {}

class MainFrame : public CFrameWnd {

protected:
  HtmlView browser;

public:
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg void OnDestroy();
  afx_msg void OnSize(UINT nType, int cx, int cy);
};

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
ON_WM_CREATE()
ON_WM_PAINT()
ON_WM_DESTROY()
ON_WM_SIZE()
END_MESSAGE_MAP()

void MainFrame::OnSize(UINT nType, int cx, int cy) {
  CRect rect;
  GetClientRect(&rect);
  browser.SetWindowPos(NULL, rect.left, rect.top, rect.right, rect.bottom,
                       SWP_NOACTIVATE | SWP_NOZORDER);
}

void MainFrame::OnPaint() { CPaintDC dc(this); }

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  CRect rc;
  GetClientRect(&rc);
  browser.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rc, this, IDC_HTML);
  IHTMLDocument2 *pDocument;
  browser.GetDHtmlDocument(&pDocument);

  CString html = "";
  int charsize = sizeof(html.GetAt(0));
  IStream *istream =
      SHCreateMemStream(reinterpret_cast<const BYTE *>(html.GetBuffer()),
                        charsize * html.GetLength());

  BSTR bstr = SysAllocString(OLESTR("<p>Hello World!</p>"));
  // Creates a new one-dimensional array
  SAFEARRAY *psaStrings = SafeArrayCreateVector(VT_VARIANT, 0, 1);

  VARIANT *param;
  HRESULT hr = SafeArrayAccessData(psaStrings, (LPVOID *)&param);
  param->vt = VT_BSTR;
  param->bstrVal = bstr;
  hr = SafeArrayUnaccessData(psaStrings);
  hr = pDocument->write(psaStrings);
  SafeArrayDestroy(psaStrings);

  return 0;
}

void MainFrame::OnDestroy() {}

class MainWindow : public CWinApp {
private:
  MainFrame *frame;

public:
  virtual BOOL InitInstance() {
    frame = new MainFrame();
    m_pMainWnd = frame;
    frame->Create(NULL, "Browser");
    frame->ShowWindow(SW_SHOW);
    frame->UpdateWindow();

    return TRUE;
  }
};

MainWindow wnd;