#include <iostream>

using namespace std;

class A
{
  private:
    char *Name;

  public:
    A()
    {
        Name = "A";
    }
    friend void Print(A m);
};

void Print(A o)
{
    cout << "o name is " << o.Name << endl;
}

int main(int argc, char **argv)
{
    A *a = new A();
    Print(*a);
    delete a;
    return 0;
}