#include <iostream>

using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    auto fn1 = []() -> void { cout << 1 << endl; };
    auto fn2 = [](int) -> void { cout << 2 << endl; };
    auto fn3 = []() -> int { return 3; };
    auto fn4 = [](int i) -> int { return i; };

    fn1();
    fn2(2);
    cout << fn3() << endl;
    cout << fn4(4) << endl;
    return 0;
}