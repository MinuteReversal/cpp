extern "C" {
#include "car.h"
}

int main(int argc, char const **argv) {
  Car *car = car_create();
  car->drive(car);
  car->color = (char *)"blue";
  car->drive(car);
  car_destroy(car);
  return 0;
}