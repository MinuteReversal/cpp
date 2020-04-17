#include <iostream>
#include <bitset>

using namespace std;

template <typename T>
void printBit(T arg)
{
  bitset<sizeof(unsigned char) * 8> b = arg;
  auto s = b.to_string();
  cout << s << endl;
}

int main(int argc, char const **argv)
{
  printBit(0xff);
  printBit(0);
  printBit(-86);
  printBit(85);
  printBit(0 & 1);
  printBit(0 | 1);
  printBit(0 ^ 1);
  printBit(!0);
  printBit(!1);
  printBit(0xff >> 1);
  printBit(0xff << 1);
  return 0;
}