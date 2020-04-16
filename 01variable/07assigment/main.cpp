#include <iostream>

int main(int argc, char const *argv[])
{
  int x(3);
  int y = 4;
  int z = {5};
  std::cout << "x+y+z=" << x + y + z << std::endl;
  return 0;
}
