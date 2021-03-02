#include <iostream>
#include <list>
using namespace std;

/**
 * 取余数
 */
int mod(int a, int b)
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

/**
 * 质数 
 */
bool isPrime(int n)
{
  if (n <= 3)
  {
    return n > 1;
  }
  for (int i = 2; i < n; i++)
  {
    if (mod(n, i) == 0)
    {
      return false;
    }
  }
  return true;
}

void display(int n)
{
  int two = 2;
  int a = two;
  int b = 0;

  while (true)
  {
    b = n / a;
    if (mod(n, a) == 0)
    {
      cout << a << ",";
      if (b == 1)
        break;
      if (isPrime(b))
      {
        cout << b << ",";
        break;
      }
      else
      {
        n = b;
        continue;
      }
    }
    a++;
  }
}

/**
 *  输入->是质数->输出
 *    ^     |
 *    |     V
 *    ----拆分合数
 */
int main(int argc, char const **argv)
{
  for (size_t i = 2; i < 30; i++)
  {
    display(i);
  }

  return 0;
}