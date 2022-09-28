/**
 * [https://www.opengl.org/archives/resources/code/samples/win32_tutorial/image.c](https://www.opengl.org/archives/resources/code/samples/win32_tutorial/image.c)
 * [https://docs.microsoft.com/en-us/windows/win32/opengl/gldrawpixels](https://docs.microsoft.com/en-us/windows/win32/opengl/gldrawpixels)
 * 加载图片
 */
#ifndef UNICODE
#define UNICODE
#endif
#include "base_opengl_window.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <windows.h>


#define IDT_TIMER1 1
#if !defined(M_PI)
#define M_PI 3.141592653F
#endif

enum StateEnum {
  NONE,
  PAN,    /* pan state bit */
  ROTATE, /* rotate state bits */
  ZOOM    /* zoom state bit */
};

/* Struct used to manage color ramps */
struct colorIndexState {
  GLfloat amb[3];   /* ambient color / bottom of ramp */
  GLfloat diff[3];  /* diffuse color / middle of ramp */
  GLfloat spec[3];  /* specular color / top of ramp */
  GLfloat ratio;    /* ratio of diffuse to specular in ramp */
  GLint indexes[3]; /* where ramp was placed in palette */
};

/*
** Each entry in this array corresponds to a color ramp in the
** palette.  The indexes member of each struct is updated to
** reflect the placement of the color ramp in the palette.
*/
#define NUM_COLORS (sizeof(colors) / sizeof(colors[0]))
struct colorIndexState colors[] = {
    {
        {0.0F, 0.0F, 0.0F},
        {0.1F, 0.6F, 0.3F},
        {1.0F, 1.0F, 1.0F},
        0.75F,
        {0, 0, 0},
    },
    {
        {0.0F, 0.0F, 0.0F},
        {0.0F, 0.2F, 0.5F},
        {1.0F, 1.0F, 1.0F},

        0.75F,
        {0, 0, 0},
    },
    {
        {0.0F, 0.05F, 0.05F},
        {0.6F, 0.0F, 0.8F},
        {1.0F, 1.0F, 1.0F},
        0.75F,
        {0, 0, 0},
    },
};

class MainWindow : public BaseOpenGLWindow<MainWindow> {
private:
  GLfloat rot[2];
  GLfloat trans[3]; /* current translation */
  unsigned *image;  /* texture image */
  int winWidth, winHeight;
  void (*idleFunc)(void);
  HDC hDCFrontBuffer;

  BOOL colorIndexMode = false;
  BOOL doubleBuffered = false;
  BOOL renderToDIB = false;

  GLfloat x, y, z;

public:
  PCWSTR ClassName() const { return L"OpenGL"; }
  void onResize(int width, int height) {
    setProjection();
    glViewport(0, 0, winWidth, winHeight);
  }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    this->winWidth = LOWORD(lParam);
    this->winHeight = HIWORD(lParam);

    switch (uMsg) {
    case WM_CREATE:
      hDC = GetDC(m_hwnd);
      SetDCPixelFormat(hDC);
      hRC = wglCreateContext(hDC);
      wglMakeCurrent(hDC, hRC);
      SetTimer(m_hwnd, IDT_TIMER1, 1000 / 60, NULL);
      init();
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
    case WM_TIMER:
      OnPaint();
      break;
    case WM_SIZE:
      /**
       *
       * <---------------DWORD--------------->
       * [00000000:00000000:00000000:00000000]
       * <-----HIWORD-----><------LOWORD----->
       *
       */
      onResize(this->winWidth, this->winHeight);
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

  void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    ** Preserve the aspect ratio of objects in the scene.
    */
    if (winWidth > winHeight) {
      GLfloat aspect = (GLfloat)winWidth / (GLfloat)winHeight;
      glFrustum(-0.5F * aspect, 0.5F * aspect, -0.5F, 0.5F, 1.0F, 3.0F);
    } else {
      GLfloat aspect = (GLfloat)winHeight / (GLfloat)winWidth;
      glFrustum(-0.5F, 0.5F, -0.5F * aspect, 0.5F * aspect, 1.0F, 3.0F);
    }
    glMatrixMode(GL_MODELVIEW);
  }

  void init() {
    GLfloat matShine = 20.00F;
    GLfloat light0Pos[4] = {0.70F, 0.70F, 1.25F, 0.00F};

    glClearColor(colors[2].diff[0], colors[2].diff[1], colors[2].diff[2], 1.0F);
    glClearIndex((GLfloat)colors[2].indexes[1]);

    setProjection();
    glTranslatef(0.0F, 0.0F, -2.0F);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glEnable(GL_LIGHT0);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    if (!this->colorIndexMode) {
      glEnable(GL_COLOR_MATERIAL);
    }
  }

  void drawTorus() {
    int numMajor = 32;
    int numMinor = 24;
    float majorRadius = 0.6F;
    float minorRadius = 0.2F;
    double majorStep = 2.0F * M_PI / numMajor;
    double minorStep = 2.0F * M_PI / numMinor;
    int i, j;

    for (i = 0; i < numMajor; ++i) {
      double a0 = i * majorStep;
      double a1 = a0 + majorStep;
      GLfloat x0 = (GLfloat)cos(a0);
      GLfloat y0 = (GLfloat)sin(a0);
      GLfloat x1 = (GLfloat)cos(a1);
      GLfloat y1 = (GLfloat)sin(a1);

      if (i & 1) {
        glColor3fv(colors[0].diff);
        glMaterialiv(GL_FRONT, GL_COLOR_INDEXES, colors[0].indexes);
      } else {
        glColor3fv(colors[1].diff);
        glMaterialiv(GL_FRONT, GL_COLOR_INDEXES, colors[1].indexes);
      }

      glBegin(GL_TRIANGLE_STRIP);
      for (j = 0; j <= numMinor; ++j) {
        double b = j * minorStep;
        GLfloat c = (GLfloat)cos(b);
        GLfloat r = minorRadius * c + majorRadius;
        GLfloat z = minorRadius * (GLfloat)sin(b);

        glNormal3f(x0 * c, y0 * c, z / minorRadius);
        glVertex3f(x0 * r, y0 * r, z);

        glNormal3f(x1 * c, y1 * c, z / minorRadius);
        glVertex3f(x1 * r, y1 * r, z);
      }
      glEnd();
    }
  }

  void doRedraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(x, 1.0F, 0.0F, 0.0F);
    glRotatef(y, 0.0F, 1.0F, 0.0F);
    glRotatef(z, 0.0F, 0.0F, 1.0F);

    drawTorus();

    glPopMatrix();

    if (renderToDIB) {
      glFinish();
      BitBlt(hDCFrontBuffer, 0, 0, winWidth, winHeight, hDC, 0, 0, SRCCOPY);
      GdiFlush();
    } else {
      glFlush();
      SwapBuffers(hDC);
    }

    x += 0.5F;
    if (x > 360.0F)
      x -= 360.0F;
    y += 0.7F;
    if (y > 360.0F)
      y -= 360.0F;
    z += 0.9F;
    if (z > 360.0F)
      z -= 360.0F;
  }

  void OnPaint() { doRedraw(); }
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine,
                     int nCmdShow) {
  MainWindow win;

  if (!win.Create(L"Learn OpenGL", WS_OVERLAPPEDWINDOW, 0, CW_USEDEFAULT,
                  CW_USEDEFAULT, 512, 512)) {
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
