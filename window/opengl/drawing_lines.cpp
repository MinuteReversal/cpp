#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "base_opengl_window.h"

class MainWindow : public BaseOpenGLWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"OpenGL"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    switch (uMsg)
    {
    case WM_CREATE:
      hDC = GetDC(m_hwnd);
      SetDCPixelFormat(hDC);
      hRC = wglCreateContext(hDC);
      wglMakeCurrent(hDC, hRC);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_CLOSE:
      wglMakeCurrent(hDC, NULL);
      ReleaseDC(m_hwnd, hDC);
      wglDeleteContext(hRC);
      DestroyWindow(m_hwnd);
      break;
    case WM_SIZE:
      /**
       * 
       * <---------------DWORD--------------->
       * [00000000:00000000:00000000:00000000]
       * <-----HIWORD-----><------LOWORD----->
       * 
       */
      glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
      PostMessage(m_hwnd, WM_PAINT, 0, 0);
      break;
    case WM_PAINT:
      BeginPaint(m_hwnd, &ps);
      OnPaint();
      EndPaint(m_hwnd, &ps);
      break;
    default:
      return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return 0;
  }
  void OnPaint()
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); //设置颜色
    glLineWidth(1);              //设置线宽度
    glBegin(GL_LINES);
    glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner
    glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner
    glEnd();
    glFlush();
  }
};

int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW, 0, CW_USEDEFAULT, CW_USEDEFAULT, 512, 512))
  {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
