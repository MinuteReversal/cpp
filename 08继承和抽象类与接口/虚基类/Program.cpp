#include <iostream>

using namespace std;
/*
*   A
* /   \
*B     C
* \   /
*   D
*/

class A
{
  public:
    void f() {}

  protected:
    int a;
};

class B : virtual public A
{
  protected:
    int b;
};

class C : virtual public A
{
  protected:
    int c;
};

class D : public B, public C
{
};

int main(int argc, char *argv)
{
    D d1;
    d1.f();
    return 0;
}