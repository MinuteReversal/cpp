#include <iostream>

using namespace std;

int main(int argc, char const **argv)
{
  int temp = 27; //2,3,7,6,12, 16, 18
  const int two = 2;
  const int three = two + 1;

  int sub2 = temp;
  int sub3 = temp;
  int count = 0;             //循环次数
  int twoRemainder = temp;   //除2余数
  int threeRemainder = temp; //除3余数

  /**
   * 操作只能用 x += 1、x -= 1，比较只能用 x == 0、x < 0
   */

  //输出2x2x3
  while (true)
  {
    count++;
    sub3 -= three;
    if (sub3 < 0)
    {
      if (threeRemainder == 0)
      {
        cout << temp;
      }
      if (three - threeRemainder < 0)
      {
        cout << threeRemainder;
      }
      break;
    }

    //除3
    if (sub3 == 0)
    {
      cout << three << ",";
      threeRemainder = count;
      sub3 = count;
      count = 0;
    }
  }
  cout << endl;
  return 0;
}