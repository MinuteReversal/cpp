#include <iostream>
#include <thread>

void fn1()
{
    while (true)
    {
        std::cout << "Playing Guitar" << std::endl;
    }
}

void fn2()
{
    while (true)
    {
        std::cout << "Sing Song" << std::endl;
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