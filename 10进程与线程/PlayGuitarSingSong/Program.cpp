#include <iostream>
#include <thread>

using namespace std;

void fn1()
{
    while (true)
    {
        cout << "Playing Guitar" << endl;
    }
}

void fn2()
{
    while (true)
    {
        cout << "Sing Song" << endl;
    }
}

int main(int argc, char **argv)
{
    thread p1(fn1);
    thread p2(fn2);

    p1.join();
    p2.join();
    return 0;
}