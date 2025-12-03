#include <cstdlib>
#include <iostream>
#include <memory>

class XData {
public:
  void Test() { index += rand(); }
  void Print() { std::cout << "XData Print" << std::endl; }

private:
  int index{0};
  char buf[1024]{0};
};

int main(int argc, char const **argv) {
  auto xdata = new XData();
  auto ptr = std::make_unique<XData>();
  std::cout << sizeof(xdata) << std::endl;
  std::cout << sizeof(ptr) << std::endl;
  return 0;
}