#pragma once
#include "car.h"
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  Car *car = new Car();
  car->go();
  delete car;
  return EXIT_SUCCESS;
}