#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../base_window/base_window.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"OpenGL"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  HDC hDC;
  HGLRC hRC;
  PAINTSTRUCT ps;
  void OnPaint();
  void SetDCPixelFormat(HDC hDC);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

void MainWindow::SetDCPixelFormat(HDC hDC)
{
  int pf;
  PIXELFORMATDESCRIPTOR pfd;
  /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  pf = ChoosePixelFormat(hDC, &pfd);
  if (pf == 0)
  {
    MessageBox(m_hwnd, L"ChoosePixelFormat() failed: Cannot find a suitable pixel format.", L"Error", MB_OK);
    return;
  }

  if (SetPixelFormat(hDC, pf, &pfd) == FALSE)
  {
    MessageBox(m_hwnd, L"SetPixelFormat() failed: Cannot set format specified.", L"Error", MB_OK);
    return;
  }
  DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
}

void MainWindow::OnPaint()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2i(0, 1);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2i(-1, -1);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2i(1, -1);
  glEnd();
  glFlush();
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW, 0, CW_USEDEFAULT, CW_USEDEFAULT, 256, 256))
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
