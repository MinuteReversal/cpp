#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char const **argv)
{
  bitset<sizeof(unsigned char) * 8> b = 0xFF;
  auto s = b.to_string();
  cout << s << endl;
  return 0;
}