#include "Windows.h"
#include "atlbase.h"
#include <atlconv.h>
#include <corecrt_malloc.h>
#include <iostream>
#include <string.h>

wchar_t *getName() {
  wchar_t *s = new wchar_t[32];
  *(s) = 'H';
  *(s + 1) = 'e';
  *(s + 2) = 'l';
  *(s + 3) = 'l';
  *(s + 4) = 'o';
  *(s + 5) = '\0';
  return s;
}

int main(int argc, char const **argv) {
  wchar_t *wname = getName();
  char* name = ATL::CW2A(wname);
  std::cout << name << std::endl;
  delete[] wname;
  return 0;
}