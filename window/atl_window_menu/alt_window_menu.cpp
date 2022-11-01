#include <atlbase.h>
#include <atlwin.h>
#include <windows.h>
#include <chrono>
#include <sstream>
#include <thread>
#include <Shlwapi.h>

#define IDC_MYATLWINDOWTEST 0x0001
#define ID_MENU_TIME 4001
#define ID_MENU_SLEEP 4002

class CMainWindow : public CWindowImpl<CMainWindow> {
	private:
		HMENU m_hMenubar;
		HMENU m_hMenu;

	public:
		BEGIN_MSG_MAP(CMainWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DESTROY, OnDestory)
		COMMAND_ID_HANDLER(ID_MENU_TIME, OnMenu1Click)
		COMMAND_ID_HANDLER(ID_MENU_SLEEP, OnSleep)
		END_MSG_MAP()

		LRESULT OnMenu1Click(WORD wNotifyCode, WORD wID, HWND hWndCtl,
							 BOOL& bHandled) {

			auto start = std::chrono::system_clock::now();
			std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<float> fs = end - start;
			std::chrono::milliseconds ms =
				std::chrono::duration_cast<std::chrono::milliseconds>(fs);
			std::stringstream str;
			// https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono
			str << ms.count();
			MessageBox(str.str().c_str(), "alert", MB_OK);

			return 0;
		}
		// https://learn.microsoft.com/en-us/cpp/atl/commandhandler?view=msvc-170
		LRESULT OnSleep(WORD wNotifyCode, WORD wID, HWND hWndCtl,
						BOOL& bHandled) {
			SYSTEMTIME start, end;
			GetSystemTime(&start);
			Sleep(1000);
			GetSystemTime(&end);
			auto duration = end.wMilliseconds - start.wMilliseconds;
			std::stringstream str;
			str << duration;
			MessageBox(str.str().c_str(), "alert", MB_OK);
			return 0;
		}
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam,
						 BOOL& bHandled) {
			m_hMenubar = CreateMenu();
			m_hMenu = CreateMenu();
			AppendMenu(m_hMenubar, MF_POPUP, (UINT_PTR)m_hMenu, "Menu");
			AppendMenu(m_hMenu, MF_STRING, ID_MENU_TIME, "time");
			AppendMenu(m_hMenu, MF_STRING, ID_MENU_SLEEP, "sleep");
			SetMenu(m_hMenubar);
			return 0;
		}

		LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam,
						BOOL& bHandled) {
			PAINTSTRUCT ps;
			this->BeginPaint(&ps);
			this->EndPaint(&ps);
			return 0;
		}

		LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam,
						  BOOL& bHandled) {
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