#include <iostream>

int main(int argc, char const *argv[])
{
  int i = 1234;
  int &ri = i;
  std::cout << ri << std::endl;
  return 0;
}
