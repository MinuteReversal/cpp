#include <iostream>
#include <array>

using namespace std;

int main(int argc, char **argv)
{
  array<int, 10> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto x : a)
  {
    std::cout << x << endl;
  }

  return 0;
}