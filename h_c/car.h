#ifndef CAR_H
#define CAR_H

class Car {
public:
  Car();
  ~Car();
  void drive();
private:
  char *color;
};
#endif