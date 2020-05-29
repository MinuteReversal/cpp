#include <iostream>
#include <string>

using namespace std;

class Car
{
private:
  /* data */
public:
  Car(/* args */);
  ~Car();
  string color = "red";
};

Car::Car(/* args */)
{
}

Car::~Car()
{
}

void showColorOfCar(Car *car)
{
  cout << "car color are " << car->color << endl;
}

int main(int argc, char const **argv)
{
  Car *const car = new Car();
  showColorOfCar(car);
  delete car;
  return 0;
}