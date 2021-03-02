#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "base_opengl_window.h"

//绘制平面
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
      glScalef(0.5, 0.5, 0.5); //缩放
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

    // glRotatef(-45, 0.0, 1.0, 0.0);  //旋转
    // glRotatef(45, 1.0, 0.0, 0.0); //旋转
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
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
        1, 1, 1, -1, -1, -1, -1, -1, 1,  // v1-v7-v2 left

        -1, -1, -1, 1, -1, -1, 1, -1, 1, // v7-v4-v3 down
        -1, -1, -1, 1, -1, 1, -1, -1, 1, // v7-v3-v2 down

        1, -1, -1, -1, -1, -1, -1, 1, -1, // v4-v7-v6 back
        1, -1, -1, -1, 1, -1, 1, 1, -1,   // v4-v6-v5 back
    };

    int count = 0;

    for (size_t i = 2; i < ARRAYSIZE(cube_strip); i += 3)
    {
      const GLfloat x = cube_strip[i - 2];
      const GLfloat y = cube_strip[i - 1];
      const GLfloat z = cube_strip[i];
      setColor(count++);
      glVertex3f(x, y, z);
    }
    count;
    glEnd();
    glFlush();
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
