#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello World" << endl;
    this_thread::sleep_for(2s);
    cout << "Hello World" << endl;
    return 0;
}