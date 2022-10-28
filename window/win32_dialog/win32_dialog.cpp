// https://learn.microsoft.com/en-us/windows/win32/dlgbox/dialog-box-types
// https://learn.microsoft.com/en-us/windows/win32/menurc/dialogex-resource?source=recommendations

// clang-format off
#include <windows.h>
#include <winnt.h>
#include <winuser.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ComDlg32.Lib")
// clang-format on

#define IDM_MENU_MAIN 40001
#define IDM_MENU_ALERT 40002
#define IDM_MENU_CONFIRM 40003
#define IDM_MENU_PROMPT 40004
#define IDM_MENU_OPEN 40005
#define IDM_MENU_SAVE 40006
#define IDM_MENU_COLOR 40007
#define IDM_MENU_FIND 40008
#define IDM_MENU_FONT 40009
#define IDM_MENU_PAGE_SETUP 40010
#define IDM_MENU_PRINT 40011
#define IDM_MENU_REPLACE 40012
#define IDM_MENU_EXIT 40013
#define IDD_PROMPT 50001

HWND hwnd;
HINSTANCE g_hInstance;
UINT uFindReplaceMsg; // message identifier for FINDMSGSTRING
HWND hDlg = NULL;     // handle of Find dialog box

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR WINAPI DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_INITDIALOG:
    break;
  default:
    return FALSE;
  }
  return TRUE;
}

void SearchFile(char *findWhat, BOOL isDown, BOOL isMatchCase) {}

UINT_PTR CALLBACK LpfrHookProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                               LPARAM lParam) {
  switch (uMsg) {
  case WM_INITDIALOG:
    ShowWindow(hDlg, SW_SHOWNORMAL);
    UpdateWindow(hDlg);
    break;
  }
  if (uMsg == uFindReplaceMsg) {
    // Get pointer to FINDREPLACE structure from lParam.
    LPFINDREPLACE lpfr = (LPFINDREPLACE)lParam;
    // If the FR_DIALOGTERM flag is set,
    // invalidate the handle identifying the dialog box.
    if (lpfr->Flags & FR_DIALOGTERM) {
      hDlg = NULL;
      return 0;
    }
    // If the FR_FINDNEXT flag is set,
    // call the application-defined search routine
    // to search for the requested string.
    if (lpfr->Flags & FR_FINDNEXT)
      SearchFile(lpfr->lpstrFindWhat, (BOOL)(lpfr->Flags & FR_DOWN),
                 (BOOL)(lpfr->Flags & FR_MATCHCASE));
    return 0;
  }
  return TRUE;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const char CLASS_NAME[] = "Sample Window Class";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window.
  g_hInstance = hInstance;
  hwnd = CreateWindow(            // Optional window styles.
      CLASS_NAME,                 // Window class
      "Learn to Program Windows", // Window text
      WS_OVERLAPPEDWINDOW,        // Window style

      // Size and position
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

      NULL,      // Parent window
      NULL,      // Menu
      hInstance, // Instance handle
      NULL       // Additional application data
  );

  if (hwnd == NULL) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    if (!IsDialogMessage(hDlg, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    HMENU hMenu = CreateMenu();
    HMENU mSubMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, "Menu");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_ALERT, "Alert");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_CONFIRM, "Confirm");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_PROMPT, "Prompt");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_OPEN, "Open File");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SAVE, "Save File");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_COLOR, "Color");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_FIND, "Find");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_REPLACE, "Replace");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_FONT, "Font");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_PAGE_SETUP,
               "Page Setup");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_PRINT, "Print");
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_EXIT, "Exit");

    SetMenu(hwnd, hMenu);
  }
    return 0;
  case WM_COMMAND: {
    if (IDM_MENU_ALERT == wParam) {
      MessageBox(hwnd, "your click sub menu", "alert", MB_OK);
    } else if (IDM_MENU_CONFIRM == wParam) {
      MessageBox(hwnd, "your click insert menu", "alert", MB_OKCANCEL);
    } else if (IDM_MENU_PROMPT == wParam) {
      DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_PROMPT), hwnd, DialogProc,
                     lParam);
      DWORD err = GetLastError();
      if (err == ERROR_RESOURCE_DATA_NOT_FOUND) {
        MessageBox(hwnd, "ERROR_RESOURCE_DATA_NOT_FOUND", "error",
                   MB_OK | MB_ICONERROR);
      }
    } else if (IDM_MENU_OPEN == wParam) {
      // https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/winui/shell/appplatform/fileisinuse/fileisinusesample.cpp
      char szPath[MAX_PATH] = {};
      OPENFILENAME ofn = {sizeof(ofn)}; // common dialog box structure
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = "All Files\0*.*\0";
      ofn.lpstrFile = szPath;
      ofn.nMaxFile = ARRAYSIZE(szPath);

      BOOL fOk = GetOpenFileName(&ofn);
      if (fOk) {
        // Open the file that was selected in
        // the Open File dialog
      }

    } else if (IDM_MENU_SAVE == wParam) {
      char szPath[MAX_PATH] = {};
      OPENFILENAME ofn = {sizeof(ofn)}; // common dialog box structure
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = "All Files\0*.*\0";
      ofn.lpstrFile = szPath;
      ofn.nMaxFile = ARRAYSIZE(szPath);

      BOOL fOk = GetSaveFileName(&ofn);
      if (fOk) {
        // Open the file that was selected in
        // the Open File dialog
      }
    } else if (IDM_MENU_COLOR == wParam) {
      // https://learn.microsoft.com/en-us/windows/win32/dlgbox/color-dialog-box
      // http://winapi.freetechsecrets.com/win32/WIN32Choosing_a_Color.htm
      // https://learn.microsoft.com/zh-cn/windows/win32/dlgbox/using-common-dialog-boxes
      COLORREF acrCustClr[16]; // array of custom colors
      CHOOSECOLOR cc = {sizeof(cc)};
      cc.lStructSize = sizeof(CHOOSECOLOR);
      cc.hwndOwner = hwnd;
      cc.Flags = CC_FULLOPEN | CC_RGBINIT;
      cc.lpCustColors = (LPDWORD)acrCustClr;

      BOOL fOk = ChooseColor(&cc);
      if (fOk) {
      }
    } else if (IDM_MENU_FIND == wParam) {
      // https://learn.microsoft.com/zh-cn/windows/win32/dlgbox/find-and-replace-dialog-boxes
      // http://winapi.freetechsecrets.com/win32/WIN32Finding_Text.htm
      // https://cplusplus.com/forum/windows/106496/
      // The crash is because the variables fr and FindWhat went out of scope.
      static FINDREPLACE fr; // common dialog box structure

      static char szFindWhat[80] = {'\0'}; // buffer receiving string

      ZeroMemory(&fr, sizeof(fr));
      fr.lStructSize = sizeof(fr);
      fr.hwndOwner = hwnd;
      fr.lpstrFindWhat = szFindWhat;
      fr.wFindWhatLen = 80;
      fr.Flags = 0; // FR_ENABLEHOOK;
      // fr.lpfnHook = LpfrHookProc;

      uFindReplaceMsg = RegisterWindowMessage(FINDMSGSTRING);
      hDlg = FindText(&fr);
      if (hDlg == NULL) {
        MessageBox(hwnd, "Create Error", "error", MB_OK);
      }

    } else if (IDM_MENU_REPLACE == wParam) {
      //The crash is because the variables fr and FindWhat went out of scope.
      static FINDREPLACE fr = {sizeof(fr)};

      static char szFindWhat[80] = {'\0'};
      static char szReplaceWith[80] = {'\0'};

      ZeroMemory(&fr, sizeof(fr));
      fr.lStructSize = sizeof(FINDREPLACE);
      fr.hwndOwner = hwnd;
      fr.Flags = 0;
      fr.lpstrFindWhat = szFindWhat;
      fr.wFindWhatLen = 80;
      fr.lpstrReplaceWith = szReplaceWith;
      fr.wReplaceWithLen = 80;

      uFindReplaceMsg = RegisterWindowMessage(FINDMSGSTRING);
      hDlg = ReplaceText(&fr);
      if (hDlg == NULL) {
        MessageBox(hwnd, "Create Error", "error", MB_OK);
      }

    } else if (IDM_MENU_FONT == wParam) {
      CHOOSEFONT cf = {sizeof(cf)};
      cf.hwndOwner = hwnd;
      BOOL fOk = ChooseFont(&cf);
      if (fOk) {
      }
    } else if (IDM_MENU_PAGE_SETUP == wParam) {
      PAGESETUPDLG psd = {sizeof(psd)};
      psd.hwndOwner = hwnd;
      PageSetupDlg(&psd);
    } else if (IDM_MENU_PRINT == wParam) {
      PRINTDLG pd = {sizeof(pd)};
      pd.hwndOwner = hwnd;
      PrintDlg(&pd);
    } else if (IDM_MENU_EXIT == wParam) {
      PostMessage(hwnd, WM_DESTROY, 0, 0L);
    }
  }
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_INITDIALOG:
    return 0;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
  }
    return 0;
  default:
    LPFINDREPLACE lpfr;

    if (uMsg == uFindReplaceMsg) {
      // Get pointer to FINDREPLACE structure from lParam.
      lpfr = (LPFINDREPLACE)lParam;

      // If the FR_DIALOGTERM flag is set,
      // invalidate the handle that identifies the dialog box.
      if (lpfr->Flags & FR_DIALOGTERM) {
        hDlg = NULL;
        return 0;
      }

      // If the FR_FINDNEXT flag is set,
      // call the application-defined search routine
      // to search for the requested string.
      if (lpfr->Flags & FR_FINDNEXT) {
        SearchFile(lpfr->lpstrFindWhat, (BOOL)(lpfr->Flags & FR_DOWN),
                   (BOOL)(lpfr->Flags & FR_MATCHCASE));
      }

      return 0;
    }
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}