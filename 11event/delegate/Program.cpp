#include <iostream>

using namespace std;

void Fn1()
{
    cout << "1" << endl;
}

void Fn2(int i)
{
    cout << i << endl;
}

int Fn3()
{
    return 3;
}

int Fn4(int i)
{
    return i;
}

int main(int argc, char **argv)
{
    void (*DFn1)() = Fn1;
    void (*DFn2)(int) = Fn2;
    int (*DFn3)() = Fn3;
    int (*DFn4)(int) = Fn4;

    DFn1();
    DFn2(2);
    cout << DFn3() << endl;
    cout << DFn4(4) << endl;

    return 0;
}