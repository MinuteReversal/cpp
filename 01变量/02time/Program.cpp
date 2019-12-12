#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

int main(int argc, char *argv)
{
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout << ctime(&now) << endl;

    auto start = chrono::system_clock::now();
    _sleep(1000);
    auto end = chrono::system_clock::now();
    auto elapsed = end - start;
    cout << elapsed.count() << endl;
    return 0;
}