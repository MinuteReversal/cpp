// https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
// http://www.cplusplus.com/forum/windows/90014/
// http://www.cplusplus.com/forum/windows/11305/
// https://stackoverflow.com/questions/37271194/wm-command-catch-button-press-in-c-win32

#include "../base_window/base_window.h"
#include <libloaderapi.h>
#include <shobjidl.h>
#include <stdlib.h>
#include <windows.h>

#define IDC_BUTTON_1 0x1
#define IDC_BUTTON_2 0x2

class CallComMainWindow : public BaseWindow<CallComMainWindow> {
public:
  PCWSTR ClassName() const { return L"Sample Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  void onCreate();
  void onPaint();
  void Button1_OnClick();
  HWND button1;
  HWND button2;
};

LRESULT CallComMainWindow::HandleMessage(UINT uMsg, WPARAM wParam,
                                         LPARAM lParam) {
  switch (uMsg) {
  case WM_COMMAND:
    if (LOWORD(wParam) == IDC_BUTTON_1) {
      Button1_OnClick();
    }
    return 0;
  case WM_CREATE:
    onCreate();
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_PAINT:
    onPaint();
    return 0;
  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return EXIT_FAILURE;
}

void CallComMainWindow::Button1_OnClick() {
  HRESULT hr =
      CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
  if (SUCCEEDED(hr)) {
    IFileOpenDialog *pFileOpen;

    // Create the FileOpenDialog object.
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                          IID_IFileOpenDialog,
                          reinterpret_cast<void **>(&pFileOpen));

    if (SUCCEEDED(hr)) {
      // Show the Open dialog box.
      hr = pFileOpen->Show(NULL);

      // Get the file name from the dialog box.
      if (SUCCEEDED(hr)) {
        IShellItem *pItem;
        hr = pFileOpen->GetResult(&pItem);
        if (SUCCEEDED(hr)) {
          PWSTR pszFilePath;
          hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

          // Display the file name to the user.
          if (SUCCEEDED(hr)) {
            MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
            CoTaskMemFree(pszFilePath);
          }
          pItem->Release();
        }
      }
      pFileOpen->Release();
    }
    CoUninitialize();
  }
}

void CallComMainWindow::onCreate() {
  //
  //按钮
  button1 = CreateWindow(
      L"BUTTON", // Predefined class; Unicode assumed
      L"PickFile",     // Button text
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
      10,                                                    // x position
      10,                                                    // y position
      100,                                                   // Button width
      100,                                                   // Button height
      m_hwnd,                                                // Parent window
      (HMENU)IDC_BUTTON_1, // For a child window, hMenu specifies the
                           // child-window identifier.
      (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);

  button2 = CreateWindow(
      L"BUTTON", // Predefined class; Unicode assumed
      L"Nothing",    // Button text
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
      120,                                                   // x position
      10,                                                    // y position
      100,                                                   // Button width
      100,                                                   // Button height
      m_hwnd,                                                // Parent window
      (HMENU)IDC_BUTTON_2,                                   // No menu.
      (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
}

/**
 * 画线
 */
void CallComMainWindow::onPaint() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);
  FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
  EndPaint(m_hwnd, &ps);
}

/**
 * 入口
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR pCmdLine, int nCmdShow) {
  CallComMainWindow win;

  if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW)) {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
