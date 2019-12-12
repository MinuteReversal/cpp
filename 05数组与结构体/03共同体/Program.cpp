#include <iostream>

using namespace std;

union AAA {
    char ch;
    int i;
    double db;
};

int main(int argc, char *argv)
{
    AAA aaa;
    aaa.ch = 'A';
    //aaa.i = 90;
    //aaa.db = 3.14;
    cout << "ch:" << aaa.ch << "i:"
         << "db:" << aaa.i << aaa.db << endl;
    return 0;
}