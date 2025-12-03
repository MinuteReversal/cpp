#include <iostream>
#include <vector>

class XData {
public:
  XData() { std::cout << "XData constructor" << std::endl; }
  XData(const XData &other) {
    std::cout << "XData copy constructor" << std::endl;
  }
  ~XData() { std::cout << "XData destructor" << std::endl; }
};

int main(int argc, char const **argv) {
  std::vector<XData> data1(3);
  auto data2 = data1; // This will invoke the copy constructor for each element
  auto data3 = std::move(data1);
  return 0;
}