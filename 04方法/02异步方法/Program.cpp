#include <iostream>
#include <string>
#include <future>

using namespace std;

string entryPort(string message)
{
    _sleep(1000);
    cout << message << endl;
    return "word";
}

int main(int argc, char **argv)
{
    auto f = async(entryPort, "hello");
    f.wait();
    cout << f.get() << endl;

    return 0;
}
