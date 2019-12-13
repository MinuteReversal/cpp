#include <iostream>

using namespace std;

int main(int argc, char *argv)
{
    char str1[] = {'h', 'e', 'l', 'l', 'o'};
    char str2[] = "world";
    char *str3 = strcat(str1, str2);
    char *str4 = "just do it";

    cout << str3 << endl;
    cout << str4 << endl;
    cout << "sizeof:" << sizeof(str1) << endl;
    return 0;
}