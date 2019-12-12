#include <iostream>

using namespace std;

int main(int argc, char *argv)
{
    int i = 123;
    int *pInt = &i;

    cout << i << endl;
    cout << *pInt << endl;

    *pInt = 456;
    cout << i << endl;
    cout << *pInt << endl;

    return 0;
}