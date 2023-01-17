#include <iostream>
#include <tuple>

std::tuple<int, int, int> rgb() { return {255, 255, 255}; }

int main(int argc, char const **argv) {

  auto [r, g, b] = rgb();
  std::cout << "r:" << r << ",g:" << g << ",b:" << b << std::endl;
  return 0;
}