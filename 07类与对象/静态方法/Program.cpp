#include <iostream>

using namespace std;

class A
{
  public:
    char static *Name;
    static void Print()
    {
        cout << Name << endl;
    }
};
char *A::Name = "A";

int main(int argc, char **argv)
{
    A::Print();
    return 0;
}