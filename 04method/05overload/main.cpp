#include <iostream>

using namespace std;
class A
{
public:
  A() {}
  ~A() {}
  int compare(int x, int y)
  {
    return x + y;
  }
  float compare(float x, float y)
  {
    return x - y;
  }
  double compare(double x, double y)
  {
    return x / y;
  }
};

int main()
{
  A a;
  cout << a.compare(10, 20) << endl;
  cout << a.compare(10.F, 20.F) << endl;
  cout << a.compare(10.0, 20.0) << endl;
  return 0;
}