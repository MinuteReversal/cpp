#include <iostream>
class A
{
public:
  A() {}
  ~A() {}
  int add(int x, int y)
  {
    return x + y;
  }
  float add(float x, float y)
  {
    return x + y;
  }
  double add(double x, double y)
  {
    return x + y;
  }
};

int main()
{
  A a;
  std::cout << a.add(10, 20) << std::endl;
  std::cout << a.add(10.0F, 20.0F) << std::endl;
  std::cout << a.add(10.0, 20.0) << std::endl;
}