#include <iostream>
#include <string>

using namespace std;
class A
{
public:
  string name = "zhy";
  A() {}
  ~A() {}
};

const A &factoryFunc()
{
  return *(new A());
}

int main(int argc, char const **argv)
{
  auto aRef = factoryFunc();
  cout << aRef.name << endl;
  aRef.name = "hello";
  cout << aRef.name << endl;
  // factoryFunc() = *(new A());
  return 0;
}