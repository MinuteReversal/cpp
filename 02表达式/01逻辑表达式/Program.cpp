#include <iostream>

using namespace std;

int main(int argc, char *argv)
{
    auto n1 = !true;
    auto n2 = !false;

    auto a1 = true && true;
    auto a2 = true && false;
    auto a3 = false && true;
    auto a4 = false && false;

    auto o1 = true || true;
    auto o2 = true || false;
    auto o3 = false || true;
    auto o4 = false || false;

    return 0;
}