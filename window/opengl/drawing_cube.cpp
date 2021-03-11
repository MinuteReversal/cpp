#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "base_opengl_window.h"

#define IDT_TIMER1 1

//绘制立方体
class MainWindow : public BaseOpenGLWindow<MainWindow>
{
public:
  PCWSTR ClassName() const { return L"OpenGL"; }
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
      SetTimer(m_hwnd, IDT_TIMER1, 1000 / 60, NULL);
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
      glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60.0, (float)width / height, 0.001, 100.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f, 0.0f, -5.0f);
      PostMessage(m_hwnd, WM_PAINT, 0, 0);
      break;
    case WM_TIMER:
      OnPaint();
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

    glRotatef(0.5f, 0.0, 1.0, 0.0); //旋转
    glRotatef(1.0f, 1.0, 0.0, 0.0); //旋转
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES); //三角

    // Create a cube
    //    v6----- v5
    //    /|      /|
    //   v1------v0|
    //   | |     | |
    //   | |v7---|-|v4
    //   |/      |/
    //   v2------v3
    // v0( 1, 1, 1)
    // v1(-1, 1, 1)
    // v2(-1,-1, 1)
    // v3( 1,-1, 1)
    // v4( 1,-1,-1)
    // v5( 1, 1,-1)
    // v6(-1, 1,-1)
    // v7(-1,-1,-1)

    //每个面有2个三角形
    const GLfloat cube_strip[] = {
        1, 1, 1, -1, 1, 1, -1, -1, 1, // v0-v1-v2 front
        1, 1, 1, -1, -1, 1, 1, -1, 1, // v0-v2-v3 front

        1, 1, 1, 1, -1, 1, 1, -1, -1, // v0-v3-v4 right
        1, 1, 1, 1, -1, -1, 1, 1, -1, // v0-v4-v5 right

        1, 1, 1, 1, 1, -1, -1, 1, -1, // v0-v5-v6 up
        1, 1, 1, -1, 1, -1, -1, 1, 1, // v0-v6-v1 up

        -1, 1, 1, -1, 1, -1, -1, -1, -1, // v1-v6-v7 left
        -1, 1, 1, -1, -1, -1, -1, -1, 1, // v1-v7-v2 left

        -1, -1, -1, 1, -1, -1, 1, -1, 1, // v7-v4-v3 down
        -1, -1, -1, 1, -1, 1, -1, -1, 1, // v7-v3-v2 down

        1, -1, -1, -1, -1, -1, -1, 1, -1, // v4-v7-v6 back
        1, -1, -1, -1, 1, -1, 1, 1, -1,   // v4-v6-v5 back
    };

    const GLint index[] = {
        0,
        1,
        2,
        0,
        2,
        3,
        0,
        3,
        4,
        0,
        4,
        5,
        0,
        5,
        6,
        0,
        6,
        1,
        1,
        6,
        7,
        1,
        7,
        2,
        7,
        4,
        3,
        7,
        3,
        2,
        4,
        7,
        6,
        4,
        6,
        5,
    };

    int count = 0;

    for (size_t i = 2; i < ARRAYSIZE(cube_strip); i += 3)
    {
      const GLfloat x = cube_strip[i - 2];
      const GLfloat y = cube_strip[i - 1];
      const GLfloat z = cube_strip[i];
      glIndexi(index[count]);
      setColor(count++);
      glVertex3f(x, y, z);
    }
    glEnd();
    glFlush();
    SwapBuffers(hDC);
  }

  void setColor(size_t index)
  {
    if (index < 6)
    {
      glColor3f(1.0f, 0.0f, 0.0f); //设置颜色
    }
    else if (index < 12)
    {
      glColor3f(0.0f, 1.0f, 0.0f); //设置颜色
    }
    else if (index < 18)
    {
      glColor3f(0.0f, 0.0f, 1.0f); //设置颜色
    }
    else if (index < 24)
    {
      glColor3f(1.0f, 1.0f, 0.0f); //设置颜色
    }
    else if (index < 30)
    {
      glColor3f(0.0f, 1.0f, 1.0f); //设置颜色
    }
    else if (index < 36)
    {
      glColor3f(1.0f, 1.0f, 1.0f); //设置颜色
    }
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
