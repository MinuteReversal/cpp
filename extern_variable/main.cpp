#include <iostream>
#include "a.cpp"

extern int a;
int main(int argc, char const *argv[])
{
  std::cout << a << std::endl;
  return 0;
}
