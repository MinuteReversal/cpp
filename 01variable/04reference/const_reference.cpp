#include <iostream>

using namespace std;

int main(int argc, char const **argv)
{
  int i = 10;
  int x = 666;
  const int &a = i;
  i = 100;
  cout << a << endl;
  return 0;
}