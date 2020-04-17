//http://c.biancheng.net/view/2337.html
#include <iostream>
using namespace std;

class A
{
private:
  int value = 0;

public:
  int operator[](int i) const { return value; } //获取元素（读取）
  int &operator[](int i) { return value; }      //获取元素（写入）
  A &operator=(const A &a);
  A() {}
  ~A() {}
};

A &A::operator=(const A &a)
{
  if (this != &a)
  {
    value = a.value;
  }
  return *this;
}

int main(int argc, char const *argv[])
{
  A a;
  a[0] = 1;
  cout << a[0] << endl;
  A a1;
  a1[0] = 333;
  a[0] = a1[0];
  cout << a[0] << endl;
  return 0;
}
