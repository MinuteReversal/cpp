#include <iostream>

using namespace std;

int r;

const int &add(const int &x, const int &y)
{
  r = x + y;
  return r;
}

int main(int argc, char const **argv)
{
  const int a = 111;
  const int b = 222;
  const int i = add(a, b);
  cout << i << endl;
  return 0;
}