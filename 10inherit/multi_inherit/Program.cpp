#include <iostream>

using namespace std;

class A
{
  public:
    char *Name;
    A()
    {
        Name = "A";
    }
};

class B
{
  public:
    char *Name;
    B()
    {
        Name = "B";
    }
};

class AB : public A, public B
{
  public:
    B::Name;
};

int main(int argc, char **argv)
{
    AB *ab = new AB();
    cout << ab->Name << endl;

    return 0;
}