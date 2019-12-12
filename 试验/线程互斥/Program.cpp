#include <iostream>
#include <list>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

const static auto s = new list<int>();
static double n = 0;

enum Semaphore
{
    empty, //同步
    full,  //同步
    mutex  //互斥
};

void P()
{
    if (s->size() > 0)
    {
    }
}

void V()
{
    if (s->size() >= 0)
    {
    }
}

void go()
{

    cout << n++ << endl;
}

int main(int argc, char *argv)
{

    while (true)
    {
        thread t1(go);
        t1.join();
    }
    return EXIT_SUCCESS;
}