// https://learn.microsoft.com/zh-tw/cpp/cpp/header-files-cpp?view=msvc-170
// https://stackoverflow.com/questions/9579930/separating-class-code-into-a-header-and-cpp-file
#include <string>

#ifndef CAR_H
#define CAR_H

class Car {
public:
  Car();
  ~Car();
  std::string color;
  void go();
};

#endif