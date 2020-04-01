#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class Car
{
public:
  string color = "red";
};

int main(int argc, char **argv)
{
  Car *car = new Car();
  cout << typeid(car).name() << endl;
  return 0;
}