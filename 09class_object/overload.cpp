class Car {
public:
  void go();
  void go(int a, int b);
};

void Car::go(){

};

void Car::go(int a, int b = 0){

};

#include <iostream>

int main(int argc, char const **argv) {

  Car *car = new Car();
  car->go();
  car->go(1);
  car->go(1, 2);
  delete car;
  return 0;
}
