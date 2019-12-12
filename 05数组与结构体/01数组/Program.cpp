#include <iostream>

using namespace std;

int main(int argc, char *argv)
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (auto i = 0; i < sizeof(a) / sizeof(*a); i++)
    {
        cout << i << endl;
    }
    return 0;
}