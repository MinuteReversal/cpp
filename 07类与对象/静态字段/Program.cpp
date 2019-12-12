#include <iostream>

using namespace std;

class A
{
  public:
    static char *Name;
    A()
    {
    }
    void Print()
    {
        cout << Name << endl;
    }
};
char *A::Name = "AAA";

int main(int argc, char *argv)
{
    A *a1 = new A();
    a1->Print();
    A a2;
    a2.Print();
    A::Name = "BBB";
    a1->Print();
    a2.Print();

    delete a1;
    return 0;
}