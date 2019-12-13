#include <iostream>
#include <string.h>

using namespace std;

void printChars(char *s)
{
    for (auto i = s; *i != '\0'; i++)
    {
        cout << *i;
    }
    cout << endl;
}

int main(int argc, char *argv[], char *envp[])
{
    char s[] = {"hello world"};
    char *a = s;
    cout << sizeof(s) / sizeof(s[0]) << endl;
    cout << sizeof(a) / sizeof(*a) << endl;
    printChars(s);
    cin >> s;
    cout << sizeof(s) / sizeof(*s) << endl;
    printChars(s);
    cout << strcasecmp(s, {"hello"}) << endl;
    return 0;
}