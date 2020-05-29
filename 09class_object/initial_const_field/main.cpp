#include <iostream>
#include <string>

using namespace std;

class Color
{
public:
  Color() {}
  ~Color() {}
  string toString()
  {
    return "red";
  }
};

class Car
{
public:
  Car() : color(new Color()) {}
  void go()
  {
    cout << this->color->toString() << endl;
  }
  ~Car() {}

private:
  Color *const color;
};

int main(int argc, char const **argv)
{
  Car *c = new Car();
  c->go();
  delete c;
  return 0;
}