#include <iostream>

using namespace std;

class Car
{
private:
  /* data */
  string color = "";

public:
  Car(/* args */);
  Car(string color);
  ~Car();
  void go();
};

Car::Car(/* args */)
{
}
Car::Car(string color)
{
  this->color = color;
}

Car::~Car()
{
}

void Car::go()
{
  cout << color << " car are go" << endl;
}

int main(int argc, char const **argv)
{
  Car car2 = {"blue"};
  Car &car3 = car2;
  car2.go();
  return 0;
}