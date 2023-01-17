#include <stdio.h>

#define PI 3.14

#define EXPAND "Hello", PI

#define FN(fmt, ...) printf(fmt, __VA_ARGS__)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char const **argv) {
  FN("%s %f\n", EXPAND);
  FN("%d\n", MAX(10, 20));
  return 0;
}