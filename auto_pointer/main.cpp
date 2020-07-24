#include <iostream>
#include <auto_ptr.h>

using namespace std;
class Car
{
private:
  /* data */
public:
  Car(/* args */);
  ~Car();
  void go();
};

Car::Car(/* args */)
{
}

Car::~Car()
{
  printf("destructor");
}
void Car::go()
{
  cout << "car are going" << endl;
}
int main(int argc, char const **argv)
{
  auto_ptr<Car> car(new Car());
  car->go();
  return 0;
}