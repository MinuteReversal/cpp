#include <iostream>

int main(int argc, char const *argv[])
{
  double i = (0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);
  std::cout << i << std::endl;
  bool b = i == 1.0;
  std::cout << b << std::endl;
  b = 0.5 + 0.5 == 1.0;
  std::cout << b << std::endl;
  return 0;
}
