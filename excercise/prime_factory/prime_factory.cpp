/**
 * numerator [/'numəretɚ/] 被除数(分子)
 * denominator [/dɪ'nɑmə'netɚ/] 除数(分母)
 * quotient [/'kwoʃnt/] 商
 * remainder [/rɪ'meɪndə/] 余数
 * 
 *          31.25 商
 * 除数  4)▔▔▔▔▔▔▔
 *         125   被除数
 *         12
 *         ------
 *           5
 *           4
 *         ------
 *           1 0
 *             8
 *         ------
 *             20
 *             20
 *         ------
 *              0 余数
 */
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

/**
 * 拆分合数
 */
list<int> split(int composite)
{
  list<int> q;
  int a = 2;
  int b = 0;
  while (true)
  {
    if (mod(composite, a) == 0)
    {
      q.push_back(a);
      b = composite / a;
      if (isPrime(b))
      {
        q.push_back(b);
        break;
      }
      else
      {
        composite = b;
        continue;
      }
    }
    a++;
  }
  return q;
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
    if (isPrime(i))
    {
      cout << i << endl;
    }
    else
    {
      for (auto const &v : split(i))
      {
        cout << v << ",";
      }
      cout << endl;
    }
  }

  return 0;
}