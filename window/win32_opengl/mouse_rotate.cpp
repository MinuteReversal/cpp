#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "base_opengl_window.h"

#define IDT_TIMER1 1

enum StateEnum
{
  NONE,
  PAN,    /* pan state bit */
  ROTATE, /* rotate state bits */
  ZOOM    /* zoom state bit */
};

//绘制平面
class MainWindow : public BaseOpenGLWindow<MainWindow>
{
private:
  GLfloat rot[2];
  HPALETTE hPalette = 0; /* custom palette (if needed) */
  GLfloat trans[3];      /* current translation */
  int omx, omy, mx, my;
  int state;

public:
  PCWSTR ClassName() const { return L"OpenGL"; }
  /**
   * @param ox {int}  原来x
   * @param nx {int}  现在x
   * @param oy {int}  原来y
   * @param ny {int}  现在y
   */
  void update(int ox, int nx, int oy, int ny)
  {
    int dx = ox - nx;
    int dy = ny - oy;
    switch (state)
    {
    case PAN:
      trans[0] -= dx / 100.0f;
      trans[1] -= dy / 100.0f;
      break;
    case ROTATE:
      rot[0] += (dy * 180.0f) / 500.0f;
      rot[1] -= (dx * 180.0f) / 500.0f;
      break;
    case ZOOM:
      trans[2] -= (dx + dy) / 100.0f;
      break;
    }
  }
  void onResize(int width, int height)
  {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / height, 0.001, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
  }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    const int width = LOWORD(lParam);
    const int height = HIWORD(lParam);
    switch (uMsg)
    {
    case WM_CREATE:
      hDC = GetDC(m_hwnd);
      SetDCPixelFormat(hDC);
      hRC = wglCreateContext(hDC);
      wglMakeCurrent(hDC, hRC);
      glEnable(GL_DEPTH_TEST);
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
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
      SetCapture(m_hwnd);
      mx = LOWORD(lParam);
      my = HIWORD(lParam);
      if (uMsg == WM_LBUTTONDOWN)
      {
        state |= ROTATE;
      }
      if (uMsg == WM_RBUTTONDOWN)
      {
        state |= PAN;
      }
      break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
      ReleaseCapture();
      state = NONE;
      break;
    case WM_MOUSEMOVE:
      if (state)
      {
        omx = mx;
        omy = my;
        mx = LOWORD(lParam);
        my = HIWORD(lParam);
        update(omx, mx, omy, my);
        PostMessage(m_hwnd, WM_PAINT, 0, 0);
      }
      break;
    default:
      return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return 0;
  }

  void OnPaint()
  {
    //    v6----- v5
    //    /|      /|
    //   v1------v0|
    //   | |     | |
    //   | |v7---|-|v4
    //   |/      |/
    //   v2------v3

    /* rotate a triangle around */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(trans[0], trans[1], trans[2]);
    glRotated(rot[0], 1.0, 0.0, 0.0);
    glRotated(rot[1], 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);

#define TOP                    \
  glIndexi(1);                 \
  glColor3f(1.0f, 0.0f, 0.0f); \
  glVertex3i(0, 1, 0)
#define FR                     \
  glIndexi(2);                 \
  glColor3f(0.0f, 1.0f, 0.0f); \
  glVertex3i(1, -1, 1)
#define FL                     \
  glIndexi(3);                 \
  glColor3f(0.0f, 0.0f, 1.0f); \
  glVertex3i(-1, -1, 1)
#define BR                     \
  glIndexi(3);                 \
  glColor3f(0.0f, 0.0f, 1.0f); \
  glVertex3i(1, -1, -1)
#define BL                     \
  glIndexi(2);                 \
  glColor3f(0.0f, 1.0f, 0.0f); \
  glVertex3i(-1, -1, -1)

    TOP;
    FL;
    FR;
    TOP;
    FR;
    BR;
    TOP;
    BR;
    BL;
    TOP;
    BL;
    FL;
    FR;
    FL;
    BL;
    BL;
    BR;
    FR;

    glEnd();
    glPopMatrix();
    glFlush();
    SwapBuffers(hDC); /* nop if singlebuffered */
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
