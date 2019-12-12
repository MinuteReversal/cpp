#include <iostream>

using namespace std;

class A
{
  public:
    void Hello()
    {
        cout << "hello" << endl;
    }
};

class B
{
  public:
    void AddEventListener(A a, void (A::*listener)())
    {
        (a.*listener)();
    }
};

int main(int argc, char *argv)
{
    A a;
    B b;
    b.AddEventListener(a, &A::Hello);
    return 0;
}