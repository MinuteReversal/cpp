#include <iostream>

using namespace std;

void CallBack(void (*fnCallback)())
{
    fnCallback();
}

void Fn1()
{
    cout << "Hello Call Back" << endl;
}

int main(int argc, char *argv)
{
    CallBack(Fn1);
    return 0;
}