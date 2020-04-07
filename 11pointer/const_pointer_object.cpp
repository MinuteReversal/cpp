#include <iostream>
#include <string>
using namespace std;

class A
{
private:
  /* data */
  string Name = "hello";

public:
  A(/* args */) {}
  string getName()
  {
    return this->Name;
  }
  void setName(string name)
  {
    this->Name = name;
  }
  ~A() {}
};

int main(int argc, char const **argv)
{
  A *const a = new A();
  cout << a->getName() << endl;
  a->setName("zhy");
  cout << a->getName() << endl;
  return 0;
}
