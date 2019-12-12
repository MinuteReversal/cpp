#include <iostream>

using namespace std;

enum Gender
{
    Male = 0,
    Female = 1
};

int main(int argc, char *argv)
{
    Gender gender = Female;
    cout << gender << endl;
    return 0;
}