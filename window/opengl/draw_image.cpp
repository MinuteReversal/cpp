/**
 * [https://www.opengl.org/archives/resources/code/samples/win32_tutorial/image.c](https://www.opengl.org/archives/resources/code/samples/win32_tutorial/image.c)
 * [https://docs.microsoft.com/en-us/windows/win32/opengl/gldrawpixels](https://docs.microsoft.com/en-us/windows/win32/opengl/gldrawpixels)
 * 加载图片
 */
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "base_opengl_window.h"
#include "opengl.h"

#define IDT_TIMER1 1

enum StateEnum
{
  NONE,
  PAN,    /* pan state bit */
  ROTATE, /* rotate state bits */
  ZOOM    /* zoom state bit */
};

class MainWindow : public BaseOpenGLWindow<MainWindow>
{
private:
  GLfloat rot[2];
  GLfloat trans[3]; /* current translation */
  unsigned *image;  /* texture image */
  int iwidth, iheight, idepth;

public:
  PCWSTR ClassName() const { return L"OpenGL"; }
  void onResize(int width, int height)
  {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(0, 0);
    glPixelZoom((float)width / iwidth, (float)height / iheight);
  }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    const int width = LOWORD(lParam);
    const int height = HIWORD(lParam);
    image = opengl_image;
    iwidth = opengl_width;
    iheight = opengl_height;
    idepth = opengl_depth;
    switch (uMsg)
    {
    case WM_CREATE:
      hDC = GetDC(m_hwnd);
      SetDCPixelFormat(hDC);
      hRC = wglCreateContext(hDC);
      wglMakeCurrent(hDC, hRC);
      break;
    case WM_DESTROY:
      KillTimer(m_hwnd, IDT_TIMER1);
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
      onResize(width, height);
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
    glDrawPixels(iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, image);
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
