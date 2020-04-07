#include <iostream>

using namespace std;

void fn1()
{
  cout << "fn1" << endl;
}

void fn2(int i)
{
  cout << "fn2" << endl;
}

int fn3()
{
  return 3;
}

int fn4(int i)
{
  return i;
}

int main(int argc, char const **argv)
{
  void (*f1)() = fn1;
  (*f1)();

  void (*f2)(int) = fn2;
  (*f2)(2);

  int (*f3)() = fn3;
  cout << "fn" << (*f3)() << endl;

  int (*f4)(int) = fn4;
  cout << "fn" << (*f4)(4) << endl;

  return 0;
}