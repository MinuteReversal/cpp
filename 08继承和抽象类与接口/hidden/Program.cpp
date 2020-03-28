#include <iostream>

using namespace std;

class A
{
public:
  A() {}
  int X;
};

class B : public A
{
public:
  B() {}
  int X; //hide
};

class C : public B
{
};

int main(int argc, char **argv)
{
  A *a = new C();
  a->X = 10;
  B *b = (B *)a;
  b->X = 100;
  C *c = (C *)b;

  cout << a->X << "," << b->X << "," << c->X << endl;

  return 0;
}