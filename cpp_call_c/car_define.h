#ifndef CAR_DEFINE_H
#define CAR_DEFINE_H
typedef struct Car {
  char *color;
  void (*drive)(struct Car *);
} Car;
#endif