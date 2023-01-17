#include "car.h"
#include <malloc.h>
#include <stdio.h>


void drive(Car *car) { printf("%s car are driving.\n", car->color); }

Car *car_create() {
  Car *car = (Car *)malloc(sizeof(Car));
  car->drive = drive;
  car->color = "red";
  return car;
}

void car_destroy(Car *car) {
  car->color = NULL;
  car->drive = NULL;
  free(car);
}
