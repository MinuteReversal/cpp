#include <iostream>

using namespace std;

void Fn1();
void Fn2(int i);
int Fn3();
int Fn4(int i);

int main(int argc, char **argv)
{
    Fn1();
    Fn2(2);
    cout << Fn3() << endl;
    cout << Fn4(4) << endl;
    return 0;
}

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