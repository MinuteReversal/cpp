#include <iostream>

using namespace std;

class A
{
  public:
    A()
    {
        char a[] = "mynameisa";
        Name = a;
    }

  private:
    char *Name;
    friend class B;
};

class B
{
  public:
    void Print(A *a)
    {
        cout << a->Name << endl;
    }
};

int main(int argc, char *argv[], char *envp[])
{
    A *a = new A();
    B *b = new B();
    b->Print(a);
    delete a;
    delete b;
    return 0;
}