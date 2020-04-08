#include <iostream>
#include <string>

using namespace std;

class A
{
public:
  string name = "A class";
  A() {}
  ~A() {}
};

class B
{
public:
  string name = "B class";
  B() {}
  ~B() {}
};

template <typename T>
const T &create()
{
  return *(new T());
}

int main(int argc, char const **argv)
{
  auto const a = create<A>();
  cout << a.name << endl;

  auto const b = create<B>();
  cout << b.name << endl;
  return 0;
}