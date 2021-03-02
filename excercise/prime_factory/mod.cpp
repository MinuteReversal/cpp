#include <iostream>

using namespace std;

int mod(int a, int b)
{
  return a - a / b * b;
}

/**
 * 用减法
 */
int mod2(int a, int b)
{
  int total = a;

  while (true)
  {
    if (total - b < 0)
      break;
    else
      total -= b;
  }

  return total;
}

int main(int argc, char const **argv)
{
  int b = 3;
  for (size_t i = 0; i < 10; i++)
  {
    cout << i % b << mod2(i, b) << endl;
  }

  return 0;
}