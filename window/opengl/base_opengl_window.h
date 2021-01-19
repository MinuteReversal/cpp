#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "../base_window/base_window.h"

template <class DERIVED_TYPE>
class BaseOpenGLWindow : public BaseWindow<DERIVED_TYPE>
{
protected:
  HDC hDC;
  HGLRC hRC;
  PAINTSTRUCT ps;

  void SetDCPixelFormat(HDC hDC)
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
      MessageBox(this->m_hwnd, L"ChoosePixelFormat() failed: Cannot find a suitable pixel format.", L"Error", MB_OK);
      return;
    }

    if (SetPixelFormat(hDC, pf, &pfd) == FALSE)
    {
      MessageBox(this->m_hwnd, L"SetPixelFormat() failed: Cannot set format specified.", L"Error", MB_OK);
      return;
    }
    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  }
};