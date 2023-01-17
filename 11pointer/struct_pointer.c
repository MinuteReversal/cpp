#include "malloc.h"
#include "stdio.h"
#include <stdlib.h>

typedef struct Car {
  char *color;
} Car, *PCar;

int main(int argc, char const *argv[]) {
  PCar car = (PCar)malloc(sizeof(Car));
  car->color = "white";
  printf("%s\n", car->color);
  free(car);
  return 0;
}