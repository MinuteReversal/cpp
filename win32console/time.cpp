
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <iostream>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
  SYSTEMTIME time;
  GetLocalTime(&time);
  std::printf("当前时间为：%2d:%2d:%2d\n", time.wHour, time.wMinute, time.wSecond);
  return 0;
}