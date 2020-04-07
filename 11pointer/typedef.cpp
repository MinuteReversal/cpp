#include <iostream>

using namespace std;

void fn1()
{
  cout << "fn1" << endl;
}

typedef void (*FN1)();

int main(int argc, char const **argv)
{
  FN1 f1 = fn1;
  f1();
  return 0;
}